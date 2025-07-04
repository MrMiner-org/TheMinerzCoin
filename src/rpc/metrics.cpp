#include "httpserver.h"
#include "metrics.h"
#include "main.h"
#include "net.h"
#include "txmempool.h"
#include <prometheus/registry.h>
#include <prometheus/gauge.h>
#include <prometheus/text_serializer.h>
#include <memory>

using namespace prometheus;

static std::shared_ptr<Registry> registry;
static Gauge* chain_height = nullptr;
static Gauge* peer_count = nullptr;
static Gauge* mempool_tx = nullptr;

static bool HTTPReq_Metrics(HTTPRequest* req, const std::string&)
{
    if (req->GetRequestMethod() != HTTPRequest::GET) {
        req->WriteReply(HTTP_BAD_METHOD, "Metrics requires GET");
        return false;
    }
    if (!registry) {
        registry = std::make_shared<Registry>();
        auto& fam = BuildGauge().Name("node_chain_height").Help("Current block height").Register(*registry);
        chain_height = &fam.Add({});
        auto& fam2 = BuildGauge().Name("node_peer_count").Help("Connected peers").Register(*registry);
        peer_count = &fam2.Add({});
        auto& fam3 = BuildGauge().Name("node_mempool_tx").Help("Mempool transactions").Register(*registry);
        mempool_tx = &fam3.Add({});
    }
    chain_height->Set(chainActive.Height());
    {
        LOCK(cs_vNodes);
        peer_count->Set(vNodes.size());
    }
    mempool_tx->Set(mempool.size());

    TextSerializer serializer;
    std::string body = serializer.Serialize(registry->Collect());
    req->WriteHeader("Content-Type", "text/plain; version=0.0.4");
    req->WriteReply(HTTP_OK, body);
    return true;
}

void StartMetricsServer()
{
    RegisterHTTPHandler("/metrics", true, HTTPReq_Metrics);
}

void StopMetricsServer()
{
    UnregisterHTTPHandler("/metrics", true);
}
