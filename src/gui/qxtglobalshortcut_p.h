/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtGui module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or modify it
** under the terms of th Common Public License, version 1.0, as published by
** IBM.
**
** This file is provided "AS IS", without WARRANTIES OR CONDITIONS OF ANY
** KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT LIMITATION, ANY
** WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT, MERCHANTABILITY OR
** FITNESS FOR A PARTICULAR PURPOSE. 
**
** You should have received a copy of the CPL along with this file.
** See the LICENSE file and the cpl1.0.txt file included with the source
** distribution for more information. If you did not receive a copy of the
** license, contact the Qxt Foundation.
** 
** <http://libqxt.sourceforge.net>  <foundation@libqxt.org>
**
****************************************************************************/
#ifndef QXTGLOBALSHORTCUT_P_H
#define QXTGLOBALSHORTCUT_P_H

#include "qxtpimpl.h"
#include "qxtglobalshortcut.h"
#include "qxtnativeeventfilter.h"
#include <QKeySequence>

class QxtGlobalShortcutPrivate : public QxtPrivate<QxtGlobalShortcut>, public QxtNativeEventFilter
{
public:
    QXT_DECLARE_PUBLIC(QxtGlobalShortcut);
    QxtGlobalShortcutPrivate();

    bool enabled;
    Qt::Key key;
    Qt::KeyboardModifiers mods;
#ifdef Q_WS_WIN
    QWidget* widget;
#endif // Q_WS_WIN
    //bool setShortcut(Qt::Key keycode, Qt::KeyboardModifiers modifiers);
    bool setShortcut(const QKeySequence& shortcut);
    bool unsetShortcut();

#if defined(Q_WS_X11)
    bool x11EventFilter(XEvent* event);
#elif defined(Q_WS_WIN)
    bool winEventFilter(MSG* msg, long* result);
#elif defined(Q_WS_MAC)
    bool macEventFilter(EventHandlerCallRef caller, EventRef event);
#endif

private:
    quint32 nativeKeycode(Qt::Key keycode) const;
    quint32 nativeModifiers(Qt::KeyboardModifiers modifiers) const;

    bool registerShortcut(quint32 nativeKey, quint32 nativeMods);
    bool unregisterShortcut(quint32 nativeKey, quint32 nativeMods);
    void activateShortcut(quint32 nativeKey, quint32 nativeMods);
};

#endif // QXTGLOBALSHORTCUT_P_H
