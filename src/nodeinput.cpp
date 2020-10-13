/*
 *  Cascade Image Editor
 *
 *  Copyright (C) 2020 The Cascade developers
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "nodeinput.h"

#include <iostream>

#include <QMouseEvent>

NodeInput::NodeInput(NodeInputType t, QWidget *parent)
    : QPushButton (parent),
      inputType(t)
{
    parentNode = static_cast<NodeBase*>(parent);
    this->resize(12, 25);

    if (t == NODE_INPUT_TYPE_RGB_FRONT)
        setObjectName("Front");
    if (t == NODE_INPUT_TYPE_RGB_BACK)
        setObjectName("Back");
    if (t == NODE_INPUT_TYPE_ALPHA)
        setObjectName("Alpha");
}

NodeInputType NodeInput::getInputType()
{
    return inputType;
}

bool NodeInput::hasConnection()
{
    if(inConnection)
    {
        return true;
    }
    return false;
}

Connection* NodeInput::getConnection()
{
    if (hasConnection())
        return inConnection;

    return nullptr;
}

void NodeInput::updateConnection()
{
    if(inConnection)
    {
        inConnection->updatePosition();
    }
}

void NodeInput::addInConnection(Connection* c)
{
    inConnection = c;
    updateConnection();
    parentNode->requestUpdate();
}

void NodeInput::removeInConnection()
{
    inConnection = nullptr;
    parentNode->requestUpdate();
}

