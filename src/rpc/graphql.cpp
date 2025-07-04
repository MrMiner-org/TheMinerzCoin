#include "httpserver.h"
#include "rpc/server.h"
#include <graphqlparser/Parser.h>
#include <graphqlparser/AST.h>

using namespace facebook::graphql;

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
    // TODO: execute against RPC table
    req->WriteHeader("Content-Type", "application/json");
    req->WriteReply(HTTP_OK, "{}");
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
