#ifndef KEYMAPPER_H
#define KEYMAPPER_H

#include <QHash>

class KeyMapper {
public:
    KeyMapper();

    uint findNativeVirtualKeyCode( Qt::Key keyCode );

private:
    QHash< Qt::Key, uint > m_keyMap;
};

#endif // KEYMAPPER_H
