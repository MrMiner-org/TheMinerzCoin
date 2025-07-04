#pragma once

bool StartWebSocketServer(unsigned short port);
void StopWebSocketServer();

void RegisterWebSocketNotifications();
void UnregisterWebSocketNotifications();
