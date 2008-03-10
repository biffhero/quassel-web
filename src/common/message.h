/***************************************************************************
 *   Copyright (C) 2005-08 by the Quassel Project                          *
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

#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <QString>
#include <QDateTime>

#include "bufferinfo.h"
#include "types.h"

class Message {
  Q_DECLARE_TR_FUNCTIONS(Message);

public:
  /** The different types a message can have for display */
  enum Type {
    Plain  = 0x0001,
    Notice = 0x0002,
    Action = 0x0004,
    Nick   = 0x0008,
    Mode   = 0x0010,
    Join   = 0x0020,
    Part   = 0x0040,
    Quit   = 0x0080,
    Kick   = 0x0100,
    Kill   = 0x0200,
    Server = 0x0400,
    Info   = 0x0800,
    Error  = 0x1000
  };

  enum Flags {
    None = 0,
    Self = 1,
    Highlight = 2,
    Redirected = 4
  };
  Q_DECLARE_FLAGS(MessageFlags, Flags)
  

  Message(BufferInfo bufferInfo = BufferInfo(), Type type = Plain, QString text = "", QString sender = "", quint8 flags = None);

  Message(QDateTime ts, BufferInfo buffer = BufferInfo(), Type type = Plain, QString text = "", QString sender = "", quint8 flags = None);

  inline MsgId msgId() const { return _msgId; }
  inline void setMsgId(MsgId id) { _msgId = id; }

  inline BufferInfo bufferInfo() const { return _bufferInfo; }
  inline QString text() const { return _text; }
  inline QString sender() const { return _sender; }
  inline Type type() const { return _type; }
  inline quint8 flags() const { return _flags; }
  inline QDateTime timestamp() const { return _timestamp; }

  void setFlags(quint8 flags);
  
  QString formattedTimestamp();
  QString formattedSender();
  QString formattedText();

  //static QString formattedToHtml(const QString &);

  /** Convert mIRC control codes to our own */
  static QString mircToInternal(QString);

  void format();

private:
  QDateTime _timestamp;
  MsgId _msgId;
  BufferInfo _bufferInfo;
  QString _text;
  QString _sender;
  Type _type;
  quint8 _flags;

  QString _formattedTimestamp, _formattedSender, _formattedText; // cache


  friend QDataStream &operator>>(QDataStream &in, Message &msg);
};

QDataStream &operator<<(QDataStream &out, const Message &msg);
QDataStream &operator>>(QDataStream &in, Message &msg);

Q_DECLARE_METATYPE(Message);
Q_DECLARE_OPERATORS_FOR_FLAGS(Message::MessageFlags)

#endif
