/*
 Copyright 2012 Tarik Sekmen.

 All Rights Reserved.

 Written by Tarik Sekmen <tarik@ilixi.org>.

 This file is part of ilixi.

 ilixi is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 ilixi is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with ilixi.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "AppThumbnail.h"
#include "Compositor.h"
#include "graphics/Painter.h"

namespace ilixi
{

  AppThumbnail::AppThumbnail(Compositor* compositor, AppInstance* instance,
      Widget* parent) :
      AppCompositor(compositor, instance, parent)
  {
    setInputMethod(KeyAndPointerInput);
    setConstraints(FixedConstraint, FixedConstraint);
    _ani.setDuration(300);
    _opacityTween = new Tween(Tween::SINE, Tween::EASE_OUT, 128, 255);
    _ani.addTween(_opacityTween);
    _ani.sigExec.connect(sigc::mem_fun(this, &AppThumbnail::tweenSlot));

    setVisible(false);
  }

  AppThumbnail::~AppThumbnail()
  {
  }

  Size
  AppThumbnail::preferredSize() const
  {
    return Size(196, 196);
  }

  void
  AppThumbnail::compose(const Rectangle& rect)
  {
  }

  void
  AppThumbnail::pointerButtonUpEvent(const PointerEvent& pointerEvent)
  {
    sigFocused(this);
    sigSelected();
  }

  void
  AppThumbnail::keyUpEvent(const KeyEvent& keyEvent)
  {
    if (keyEvent.keySymbol == DIKS_SPACE)
      sigSelected();
  }

  void
  AppThumbnail::focusInEvent()
  {
    sigFocused(this);
//    _ani.stop();
//    _opacityTween->setInitialValue(128);
//    _opacityTween->setEndValue(255);
//    _ani.start();
  }

  void
  AppThumbnail::focusOutEvent()
  {
//    _ani.stop();
//    _opacityTween->setInitialValue(255);
//    _opacityTween->setEndValue(128);
//    _ani.start();
  }

  void
  AppThumbnail::tweenSlot()
  {
//    setOpacity(_opacityTween->value());
    update();
  }

} /* namespace ilixi */
