// This file belongs to the "MiniCore" game engine.
// Copyright (C) 2010 Jussi Lind <jussi.lind@iki.fi>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA  02110-1301, USA.
//

#include "mcshape.hh"
#include "mcshapeview.hh"
#include "mccamera.hh"

#include <cassert>

MCUint MCShape::m_typeCount = 0;

MCShape::MCShape(MCShapeView * pView)
: m_pParent(nullptr)
, m_angle(0)
{
    if (pView)
    {
        setView(pView);
    }

    // Set default shadow offset
    setShadowOffset(MCVector2dF(2, -2));
}

void MCShape::setParent(MCObject & parent)
{
    m_pParent = &parent;
}

MCObject & MCShape::parent() const
{
    assert(m_pParent);
    return *m_pParent;
}

MCUint MCShape::registerType()
{
    return ++MCShape::m_typeCount;
}

MCShape::~MCShape()
{
}

void MCShape::setView(MCShapeView * p)
{
    m_pView.reset(p);
}

void MCShape::setView(std::shared_ptr<MCShapeView> p)
{
    m_pView = p;
}

MCShapeView * MCShape::view() const
{
    return m_pView.get();
}

void MCShape::render(MCCamera * p)
{
    if (m_pView)
    {
        m_pView->render(m_location, m_angle, p);
    }
}

void MCShape::renderShadow(MCCamera * p)
{
    if (m_pView)
    {
        m_pView->renderShadow(
            m_location + MCVector3dF(m_shadowOffset), m_angle, p);
    }
}

void MCShape::renderScaled(MCFloat wr, MCFloat hr, MCCamera * p)
{
    if (m_pView)
    {
        m_pView->renderScaled(m_location, m_angle, wr, hr, p);
    }
}

void MCShape::renderShadowScaled(MCFloat wr, MCFloat hr, MCCamera * p)
{
    if (m_pView)
    {
        m_pView->renderShadowScaled(
            m_location + MCVector3dF(m_shadowOffset), m_angle, wr, hr, p);
    }
}

void MCShape::translate(const MCVector3dF & p)
{
    m_location = p;
}

const MCVector3dF & MCShape::location() const
{
    return m_location;
}

void MCShape::setShadowOffset(const MCVector2dF & p)
{
    m_shadowOffset = p;
}

void MCShape::rotate(MCFloat newAngle)
{
    m_angle = newAngle;
}

MCFloat MCShape::angle() const
{
    return m_angle;
}