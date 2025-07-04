#include "validationinterface.h"
#include <libwebsockets.h>
#include <list>
#include <string>

static struct lws_context* g_ctx = nullptr;
static std::list<struct lws*> g_clients;

static int ws_callback(struct lws* wsi, enum lws_callback_reasons reason,
                       void* /*user*/, void* in, size_t len)
{
    switch (reason) {
    case LWS_CALLBACK_ESTABLISHED:
        g_clients.push_back(wsi);
        break;
    case LWS_CALLBACK_CLOSED:
        g_clients.remove(wsi);
        break;
    case LWS_CALLBACK_RECEIVE:
        /* ignore incoming data */
        break;
    default:
        break;
    }
    return 0;
}

static struct lws_protocols protocols[] = {
    {"events", ws_callback, 0, 4096, 0, nullptr, 0},
    {nullptr, nullptr, 0, 0, 0, nullptr, 0}
};

bool StartWebSocketServer(unsigned short port)
{
    struct lws_context_creation_info info{};
    info.port = port;
    info.protocols = protocols;
    g_ctx = lws_create_context(&info);
    return g_ctx != nullptr;
}

void StopWebSocketServer()
{
    if (g_ctx) {
        lws_context_destroy(g_ctx);
        g_ctx = nullptr;
    }
}

static void broadcast(const std::string& msg)
{
    unsigned char buf[LWS_PRE + 1024];
    size_t n = msg.size();
    if (n > 1024) return;
    memcpy(&buf[LWS_PRE], msg.data(), n);
    for (auto* wsi : g_clients) {
        lws_write(wsi, &buf[LWS_PRE], n, LWS_WRITE_TEXT);
    }
}

class CWebsocketNotifier : public CValidationInterface
{
    void UpdatedBlockTip(const CBlockIndex* pindex) override
    {
        if (!pindex) return;
        broadcast("block:" + pindex->GetBlockHash().GetHex());
    }

    void SyncTransaction(const CTransaction& tx, const CBlockIndex* /*pindex*/, const CBlock* /*pblock*/, const bool /*fConnect*/) override
    {
        broadcast("tx:" + tx.GetHash().GetHex());
    }
};

static CWebsocketNotifier g_notifier;

void RegisterWebSocketNotifications()
{
    RegisterValidationInterface(&g_notifier);
}

void UnregisterWebSocketNotifications()
{
    UnregisterValidationInterface(&g_notifier);
}
