/***************************************************************************
*   Copyright (C) 2005-09 by the Quassel Project                          *
*   devel@quassel-irc.org                                                 *
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) version 3.                                           *
*                                                                         *
*   This program is distributed in the hope that it will be useful,       *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
*   GNU General Public License for more details.                          *
*                                                                         *
*   You should have received a copy of the GNU General Public License     *
*   along with this program; if not, write to the                         *
*   Free Software Foundation, Inc.,                                       *
*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
***************************************************************************/

#ifndef CLIENTUSERINPUTHANDLER_H_
#define CLIENTUSERINPUTHANDLER_H_

#include "basichandler.h"

class BufferInfo;
class NetworkId;

class ClientUserInputHandler : public BasicHandler {
  Q_OBJECT

public:
  ClientUserInputHandler(QObject *parent = 0);

public Q_SLOTS:
  void handleUserInput(const BufferInfo &bufferInfo, const QString &msg);

Q_SIGNALS:
  void sendInput(const BufferInfo &, const QString &);

private Q_SLOTS:
  void completionSuffixChanged(const QVariant &);

  void handleExec(const BufferInfo &bufferInfo, const QString &execString);
  void handleJoin(const BufferInfo &bufferInfo, const QString &text);
  void handleQuery(const BufferInfo &bufferInfo, const QString &text);
  void defaultHandler(const QString &cmd, const BufferInfo &bufferInfo, const QString &text);

private:
  QRegExp _nickRx;

  //! Helper method for switching to new/existing buffers
  /** Immediately switches to the given buffer or schedules a switch for whenever
    * the buffer is created
    */
  void switchBuffer(const NetworkId &networkId, const QString &bufferName);
};

#endif
