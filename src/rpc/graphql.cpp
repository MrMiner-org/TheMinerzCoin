#include "httpserver.h"
#include "rpc/server.h"
#include <graphqlparser/Parser.h>
#include <graphqlparser/AST.h>
#include <regex>

using namespace facebook::graphql;

static std::map<std::string, std::string> ParseArgs(const std::string& args)
{
    std::map<std::string, std::string> out;
    std::regex re("(\\w+)\\s*:\\s*\"?([^,\"]+)\"?");
    auto begin = std::sregex_iterator(args.begin(), args.end(), re);
    auto end = std::sregex_iterator();
    for (auto it = begin; it != end; ++it) {
        out[(*it)[1]] = (*it)[2];
    }
    return out;
}

static UniValue ExecuteField(const std::string& name, const std::map<std::string, std::string>& args)
{
    if (name == "block") {
        auto it = args.find("height");
        if (it == args.end()) throw std::runtime_error("height required");
        int height = atoi(it->second.c_str());
        UniValue p1(UniValue::VARR); p1.push_back(height);
        UniValue hash = tableRPC.execute("getblockhash", p1);
        UniValue p2(UniValue::VARR); p2.push_back(hash.get_str()); p2.push_back(1);
        UniValue block = tableRPC.execute("getblock", p2);
        UniValue res(UniValue::VOBJ);
        res.push_back(Pair("hash", block["hash"].get_str()));
        res.push_back(Pair("height", height));
        return res;
    } else if (name == "transaction") {
        auto it = args.find("txid");
        if (it == args.end()) throw std::runtime_error("txid required");
        UniValue p(UniValue::VARR); p.push_back(it->second); p.push_back(true);
        UniValue tx = tableRPC.execute("getrawtransaction", p);
        UniValue res(UniValue::VOBJ);
        res.push_back(Pair("txid", it->second));
        if (tx.exists("hex")) res.push_back(Pair("hex", tx["hex"].get_str()));
        return res;
    } else if (name == "mempool") {
        UniValue p(UniValue::VARR); p.push_back(false);
        UniValue mp = tableRPC.execute("getrawmempool", p);
        UniValue arr(UniValue::VARR);
        for (size_t i = 0; i < mp.size(); ++i) {
            UniValue obj(UniValue::VOBJ);
            obj.push_back(Pair("txid", mp[i].get_str()));
            arr.push_back(obj);
        }
        return arr;
    } else if (name == "wallet") {
        UniValue info = tableRPC.execute("getwalletinfo", UniValue(UniValue::VARR));
        UniValue res(UniValue::VOBJ);
        auto it = args.find("name");
        if (it != args.end()) res.push_back(Pair("name", it->second));
        if (info.exists("balance")) res.push_back(Pair("balance", info["balance"]));
        else res.push_back(Pair("balance", NullUniValue));
        return res;
    } else if (name == "networkStats") {
        UniValue blocks = tableRPC.execute("getblockcount", UniValue(UniValue::VARR));
        UniValue diff = tableRPC.execute("getdifficulty", UniValue(UniValue::VARR));
        UniValue stake = tableRPC.execute("getstakinginfo", UniValue(UniValue::VARR));
        UniValue res(UniValue::VOBJ);
        res.push_back(Pair("blocks", blocks.get_int()));
        if (diff.isObject() && diff.exists("proof-of-stake"))
            res.push_back(Pair("difficulty", diff["proof-of-stake"]));
        if (stake.isObject() && stake.exists("netstakeweight"))
            res.push_back(Pair("stakeWeight", stake["netstakeweight"]));
        return res;
    } else if (name == "sendRawTransaction") {
        auto it = args.find("hex");
        if (it == args.end()) throw std::runtime_error("hex required");
        UniValue p(UniValue::VARR); p.push_back(it->second);
        UniValue txid = tableRPC.execute("sendrawtransaction", p);
        UniValue res(UniValue::VOBJ);
        res.push_back(Pair("txid", txid.get_str()));
        return res;
    }
    throw std::runtime_error("unsupported field");
}

static UniValue ExecuteGraphQL(const std::string& query)
{
    UniValue result(UniValue::VOBJ);
    std::regex field_re("(\\w+)\\s*(?:\\(([^)]*)\\))?");
    auto begin = std::sregex_iterator(query.begin(), query.end(), field_re);
    auto end = std::sregex_iterator();
    for (auto it = begin; it != end; ++it) {
        std::string name = (*it)[1];
        if (name == "query" || name == "mutation") continue;
        std::string args_str = (*it)[2];
        auto args = ParseArgs(args_str);
        result.push_back(Pair(name, ExecuteField(name, args)));
    }
    return result;
}

static bool HTTPReq_GraphQL(HTTPRequest* req, const std::string&)
{
    if (req->GetRequestMethod() != HTTPRequest::POST) {
        req->WriteReply(HTTP_BAD_METHOD, "GraphQL requires POST");
        return false;
    }
    std::string body = req->ReadBody();
    std::string query = body;
    std::string error;
    auto ast = parseString(query, &error);
    if (!ast) {
        req->WriteReply(HTTP_BAD_REQUEST, error);
        return false;
    }
    try {
        UniValue out = ExecuteGraphQL(query);
        req->WriteHeader("Content-Type", "application/json");
        req->WriteReply(HTTP_OK, out.write());
    } catch (const std::exception& e) {
        req->WriteReply(HTTP_BAD_REQUEST, e.what());
        return false;
    }
    return true;
}

void StartGraphQLServer()
{
    RegisterHTTPHandler("/graphql", true, HTTPReq_GraphQL);
}

void StopGraphQLServer()
{
    UnregisterHTTPHandler("/graphql", true);
}
