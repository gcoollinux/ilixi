/*
 Copyright 2010-2012 Tarik Sekmen.

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

#ifndef HORIZONTALSWITCHER_H_
#define HORIZONTALSWITCHER_H_

#include "Switcher.h"
#include "HorizontalScroller.h"
#include <ui/ScrollArea.h>
#include <ui/HBoxLayout.h>
#include <ui/ToolButton.h>

namespace ilixi
{
/*!
 * Allows switching between applications using a ScrollArea.
 */
class HorizontalSwitcher : public Switcher
{
public:
    /*!
     * Initialises ScrollArea, layout and animations.
     */
    HorizontalSwitcher(Widget* parent = 0);

    /*!
     * Destructor.
     */
    virtual
    ~HorizontalSwitcher();

    virtual Size
    preferredSize() const;

    virtual void
    addThumb(AppThumbnail* thumb);

    virtual void
    removeThumb(AppThumbnail* thumb);

    virtual void
    scrollTo(AppThumbnail* thumb);

    virtual void
    show();

    virtual void
    hide();

    virtual void
    setOptimalGeometry(int width, int height);

    /*!
     * Scrolls to next thumbnail.
     */
    virtual void
    scrollToNext();

    /*!
     * Scrolls to previous thumbnail.
     */
    virtual void
    scrollToPrevious();

protected:
    Image* _bg;
    ToolButton* _left;
    ToolButton* _right;
    HorizontalScroller* _scroller;

    TweenAnimation _anim;
    Tween* _tween;
    int _anchorY;
    int _num2Slide;

    virtual void
    compose(const PaintEvent& event);

    void
    updateSwitcherGeometry();

private:
    virtual void
    tweenSlot();

    virtual void
    tweenEndSlot();
};

} /* namespace ilixi */
#endif /* HORIZONTALSWITCHER_H_ */
