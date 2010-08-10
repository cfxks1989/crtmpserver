/* 
 *  Copyright (c) 2010,
 *  Gavriloaie Eugen-Andrei (shiretu@gmail.com)
 *
 *  This file is part of crtmpserver.
 *  crtmpserver is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  crtmpserver is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with crtmpserver.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef NET_EPOLL
#include "netio/epoll/iohandler.h"
#include "netio/epoll/iohandlermanager.h"

uint32_t IOHandler::_idGenerator = 0;

IOHandler::IOHandler(int32_t inboundFd, int32_t outboundFd, IOHandlerType type) {
	_type = type;
	_id = _idGenerator++;
	_inboundFd = inboundFd;
	_outboundFd = outboundFd;
	_pToken = NULL;
	IOHandlerManager::RegisterIOHandler(this);
}

IOHandler::~IOHandler() {
	IOHandlerManager::UnRegisterIOHandler(this);
}

void IOHandler::SetIOHandlerManagerToken(IOHandlerManagerToken *pToken) {
	_pToken = pToken;
}

IOHandlerManagerToken * IOHandler::GetIOHandlerManagerToken() {
	return _pToken;
}

uint32_t IOHandler::GetId() {
	return _id;
}

int32_t IOHandler::GetInboundFd() {
	return _inboundFd;
}

int32_t IOHandler::GetOutboundFd() {
	return _outboundFd;
}

IOHandlerType IOHandler::GetType() {
	return _type;
}

string IOHandler::IOHTToString(IOHandlerType type) {
	switch (type) {
		case IOHT_ACCEPTOR:
			return "IOHT_ACCEPTOR";
		case IOHT_TCP_CARRIER:
			return "IOHT_TCP_CARRIER";
		case IOHT_UDP_CARRIER:
			return "IOHT_UDP_CARRIER";
		case IOHT_TCP_CONNECTOR:
			return "IOHT_TCP_CONNECTOR";
		case IOHT_TIMER:
			return "IOHT_TIMER";
		case IOHT_INBOUNDNAMEDPIPE_CARRIER:
			return "IOHT_INBOUNDNAMEDPIPE_CARRIER";
		default:
			return format("#unknown: %d#", type);
	}
}

#endif /* NET_EPOLL */


