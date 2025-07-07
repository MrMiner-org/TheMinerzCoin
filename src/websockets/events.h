// Copyright (c) 2022-2025 The TheMinerzCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

bool StartWebSocketServer(unsigned short port);
void StopWebSocketServer();

void RegisterWebSocketNotifications();
void UnregisterWebSocketNotifications();
