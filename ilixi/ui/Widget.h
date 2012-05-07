/*
 Copyright 2011 Tarik Sekmen.

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

#ifndef ILIXI_WIDGET_H_
#define ILIXI_WIDGET_H_

#include "graphics/Surface.h"
#include "types/Enums.h"
#include "graphics/Stylist.h"
#include "types/Event.h"
#include <list>
#include <string>
#include <sigc++/signal.h>
#include "ilixiConfig.h"

namespace ilixi
{
  class EventManager;
  class WindowWidget;
  class Window;

  //! Base class for all GUI objects.
  /*!
   * The widget class is at the core of all UI elements. It creates a surface
   * to paint itself, maintains a list of children widgets and receives input events.
   */
  class Widget : virtual public sigc::trackable
  {
    friend class Application; // sets _stylist.
    friend class WindowWidget; // sets RootWindow.
    friend class EventManager;
    friend class WidgetLayout;
    friend class ScrollArea; // Blit

  public:
    /*!
     * Constructor.
     *
     * @param parent widget's parent.
     */
    Widget(Widget* parent = 0);

    /*!
     * Copy constructor.
     *
     * @param widget
     * @param parent
     */
    Widget(const Widget& widget);

    /*!
     * Destructor.
     *
     * Deletes children. Releases surface. Removes itself from the UIManager.
     */
    virtual
    ~Widget();

    /*!
     * Returns x coordinate of the widget relative to its parent.
     */
    int
    x() const;

    /*!
     * Returns y coordinate of the widget relative to its parent.
     */
    int
    y() const;

    /*!
     * Returns absolute x coordinate of the widget in window coordinates.
     * Value depends on widget's geometry flag and whether it has a parent.
     */
    int
    absX() const;

    /*!
     * Returns absolute y coordinate of the widget in window coordinates.
     * Value depends on widget's geometry flag and whether it has a parent.
     */
    int
    absY() const;

    /*!
     * Returns relative position (x, y) inside parent widget.
     */
    Point
    position() const;

    /*!
     * Returns height of widget.
     */
    int
    height() const;

    /*!
     * Returns width of widget.
     */
    int
    width() const;

    /*!
     *  Returns size (width, height) of widget.
     */
    Size
    size() const;

    /*!
     * Returns absolute geometry of the widget.
     */
    const Rectangle&
    frameGeometry() const;

    /*!
     * Returns surface geometry of the widget.
     */
    Rectangle
    surfaceGeometry() const;

    /*!
     * Returns minimum height for widget.
     *
     * @sa setMinSize()
     */
    int
    minHeight() const;

    /*!
     * Returns minimum width for widget.
     *
     * @sa setMinSize()
     */
    int
    minWidth() const;

    /*!
     * Returns the widget's minimum size.
     */
    Size
    minSize() const;

    /*!
     * Returns maximum height for widget.
     *
     * @sa setMaxSize()
     */
    int
    maxHeight() const;

    /*!
     * Returns maximum width for widget.
     *
     * @sa setMaxSize()
     */
    int
    maxWidth() const;

    /*!
     * Returns the widget's maximum size.
     */
    Size
    maxSize() const;

    /*!
     * Returns the height of the widget given its width.
     *
     * This method is used by a layout in order to shrink or enlarge
     * widgets if they allow it.
     *
     * If widget does not have FixedConstraint on y-axis and can shrink or enlarge on x-axis,
     * you should reimplement it in derived classes.
     *
     * @param width Proposed width for widget.
     *
     * @sa preferredSize()
     */
    virtual int
    heightForWidth(int width) const;

    /*!
     * Returns the preferred size for the widget.
     *
     * This method is used by a layout in order to determine a sensible
     * initial size for widget.
     *
     * By default this method returns an empty Size() which
     * indicates that widget does not care about its size.
     *
     * You should reimplement this method if you want your widget to behave properly
     * inside containers such as layouts.
     *
     * @sa heightForWidth()
     */
    virtual Size
    preferredSize() const;

    /*!
     * Returns true if widget is enabled.
     *
     * A widget is considered disabled if its parent is disabled.
     *
     * Only enabled widgets can receive focus and input events.
     */
    bool
    enabled() const;

    /*!
     * Returns true if widget is visible.
     *
     * A widget is considered invisible if its parent is invisible.
     *
     * Only visible widgets can receive focus and input events.
     */
    bool
    visible() const;

    /*!
     * Returns widget's opacity.
     */
    u8
    opacity() const;

    /*!
     * Returns true if widget has focus.
     *
     * A widget can receive incoming key events, If it is enabled, visible and has focus.
     */
    bool
    hasFocus() const;

    /*!
     * Returns true if pointer is over widget.
     */
    bool
    exposed() const;

    /*!
     * Returns true if pointer is pressed over widget.
     */
    bool
    pressed() const;

    /*!
     * Returns current widget state.
     *
     * @sa enabled(), visible(), hasFocus(), exposed()
     */
    WidgetState
    state() const;

    /*!
     * Returns true if widget is enabled, visible and has pointer input capability.
     */
    bool
    acceptsPointerInput() const;

    /*!
     * Returns true if widget is enabled, visible and has key input capability.
     */
    bool
    acceptsKeyInput() const;

    /*!
     * Returns input method flag for widget.
     *
     * This flag is used to determine which input events a widget is
     * capable of processing.
     *
     * By default a widget may not accept any input events at all.
     */
    WidgetInputMethod
    inputMethod() const;

    /*!
     * Returns widget's resize constraint on x-axis.
     */
    virtual WidgetResizeConstraint
    xConstraint() const;

    /*!
     * Returns widget's resize constraint on y-axis.
     */
    virtual WidgetResizeConstraint
    yConstraint() const;

    /*!
     * Moves widget to given coordinates inside its parent.
     *
     * @param x coordinate for top-left point.
     * @param y coordinate for top-left point.
     * @sa setX(), setY()
     */
    void
    moveTo(int x, int y);

    /*!
     * Moves widget to point inside its parent.
     *
     * @sa setX(), setY()
     */
    void
    moveTo(const Point& point);

    /*!
     * Sets the widget's surface x-coordinate (top-left) inside its parent.
     *
     * @param x coordinate for top-left point.
     */
    void
    setX(int x);

    /*!
     * Sets the widget's surface y-coordinate (top-left) inside its parent.
     *
     * @param y coordinate for top-left point.
     */
    void
    setY(int y);

    /*!
     * Sets the widget's surface height in pixels.
     *
     * @param height in pixels
     */
    void
    setHeight(int height);

    /*!
     * Sets the widget's surface width in pixels.
     *
     * @param width in pixels.
     */
    void
    setWidth(int width);

    /*!
     * Sets the widget's dimensions.
     *
     * @param width in pixels.
     * @param height in pixels
     */
    void
    setSize(int width, int height);

    /*!
     * Sets the widget's dimensions.
     *
     * @param size in pixels.
     */
    void
    setSize(const Size &size);

    /*!
     * Sets widget's surface geometry.
     *
     * @param x coordinate for top-left point.
     * @param y coordinate for top-left point.
     * @param width in pixels.
     * @param height in pixels
     */
    void
    setGeometry(int x, int y, int width, int height);

    /*!
     * Sets widget's minimum size.
     *
     * Widget's size can not be smaller than this.
     *
     * @param minSize in pixels.
     */
    void
    setMinimumSize(const Size &minSize);

    /*!
     * Sets widget's minimum size.
     *
     * Widget's size can not be smaller than this.
     *
     * @param minWidth in pixels.
     * @param minHeight in pixels
     */
    void
    setMinimumSize(int minWidth, int minHeight);

    /*!
     * Sets widget's maximum size.
     *
     * Widget's size can not be larger than this.
     *
     * @param maxSize in pixels.
     */
    void
    setMaximumSize(const Size &maxSize);

    /*!
     * Sets widget's maximum size.
     *
     * Widget's size can not be larger than this.
     *
     * @param maxWidth in pixels.
     * @param maxHeight in pixels
     */
    void
    setMaximumSize(int maxWidth, int maxHeight);

    /*!
     * Sets widget's resize constraint on x axis.
     *
     * @param constraint Default is NoConstraint.
     */
    void
    setXConstraint(WidgetResizeConstraint constraint = NoConstraint);

    /*!
     * Sets widget's resize constraint on y axis.
     *
     * @param constraint Default is NoConstraint.
     */
    void
    setYConstraint(WidgetResizeConstraint constraint = NoConstraint);

    /*!
     * Sets widget's resize constraints on x and y axis.
     *
     * @param x Default is NoConstraint.
     * @param y Default is NoConstraint.
     */
    void
    setConstraints(WidgetResizeConstraint x = NoConstraint,
        WidgetResizeConstraint y = NoConstraint);

    /*!
     * Sets widget's state to enabled and calls update() if widget is disabled.
     */
    void
    setEnabled();

    /*!
     * Sets widget's enabled flag to false and calls update() if widget is enabled.
     */
    void
    setDisabled();

    /*!
     * Sets widget's visibility.
     *
     * Hidden widgets are not drawn whether they are changed or not.
     *
     * @param visible False if Widget is hidden, true otherwise. Default true.
     */
    virtual void
    setVisible(bool visible = true);

    /*!
     * Sets widget's opacity.
     */
    void
    setOpacity(u8 opacity);

    /*!
     * Assigns key input focus to widget if the widget accepts key inputs.
     *
     * @sa acceptsKeyInput()
     */
    void
    setFocus();

    /*!
     * Clears key input focus from widget.
     *
     * If widget has focus, focusOutEvent is called.
     */
    void
    clearFocus();

    /*!
     * Sets widget's input method.
     *
     * @param method
     */
    void
    setInputMethod(WidgetInputMethod method);

    /*!
     * This method is used to enable or disable pointer motion events.
     * By default pointer tracking is disabled.
     *
     * @param pointerTracking if true widget acquires pointer tracking capability.
     */
    void
    setPointerTracking(bool pointerTracking);

    /*!
     * Sets the parent of widget.
     */
    void
    setParent(Widget* parent);

    /*!
     * Invokes widget's compose method only if widget is visible and target area
     * intersects with widget's absolute geometry.
     *
     * Warning: You should not override this method unless you know what you are doing.
     *
     * @param targetArea Bounding rectangle to paint in absolute coordinates.
     *
     * @sa compose()
     */
    virtual void
    paint(const Rectangle& targetArea);

    /*!
     * Repaints widget immediately without any clipping.
     *
     * This method is useful if widget need to paint itself repetitively, e.g.
     * animations.
     *
     * You should use update() method if you need to simply redraw widget and its contents.
     *
     * @sa update()
     */
    void
    repaint();

    /*!
     * Repaints widget immediately using clipping.
     *
     * @param rect Bounding rectangle to repaint in absolute coordinates.
     */
    virtual void
    repaint(const Rectangle& rect);

    /*!
     * Repaints widget and updates parent window inside main event loop.
     *
     * Widgets intersecting this widget's frame geometry
     * are also painted.
     *
     * @sa repaint()
     */
    void
    update();

    /*!
     * This method will repaint inside given rectangle.
     *
     * @param rect Bounding rectangle to update in absolute coordinates.
     */
    void
    update(const Rectangle& rect);

    /*!
     * Invalidates parent layout and force it to tile again on next paint.
     */
    virtual void
    doLayout();

    /*!
     * Returns neighbour widget in given direction.
     */
    Widget*
    getNeighbour(Direction direction) const;

    /*!
     * Sets neighbour widget in given direction.
     *
     * @param direction
     * @param neightbour
     */
    void
    setNeighbour(Direction direction, Widget* neightbour);

    /*!
     * Sets neighbours of widget.
     *
     * @param top
     * @param bottom
     * @param left
     * @param right
     */
    void
    setNeighbours(Widget* top, Widget* bottom, Widget* left, Widget* right);

    /*!
     * Maps the given rectangle in absolute coordinates to local coordinates.
     *
     * @param rect Rectangle in absolute coordinates.
     */
    Rectangle
    mapToSurface(const Rectangle& rect) const;

    /*!
     * Maps the given values in absolute coordinates to local coordinates.
     *
     * @param x absolute coordinate in pixels.
     * @param y absolute coordinate in pixels.
     * @param width in pixels.
     * @param height in pixels.
     */
    Rectangle
    mapToSurface(int x, int y, int width, int height) const;

    /*!
     * Maps the given point in absolute coordinates to local coordinates.
     *
     * @param point in absolute coordinates.
     */
    Point
    mapToSurface(const Point& point) const;

    /*!
     * Maps the given rectangle in local coordinates to absolute coordinates.
     *
     * @param rect Rectangle in local coordinates.
     */
    Rectangle
    mapFromSurface(const Rectangle& rect) const;

    /*!
     * Maps the given values in local coordinates to absolute coordinates.
     *
     * @param x local coordinate in pixels.
     * @param y local coordinate in pixels.
     * @param width in pixels.
     * @param height in pixels.
     */
    Rectangle
    mapFromSurface(int x, int y, int width, int height) const;

    /*!
     * Maps the given point in local coordinates to absolute coordinates.
     *
     * @param point in local coordinates.
     */
    Point
    mapFromSurface(const Point& point) const;

    /*!
     * Consumes a pointer event and calls event handling methods if the event is inside widget.
     *
     * @param pointerEvent in frame (absolute) coordinates.
     *
     * @return True if event is consumed, false otherwise.
     */
    virtual bool
    consumePointerEvent(const PointerEvent& pointerEvent);

    /*!
     * Calls appropriate key event handler method and returns true.
     *
     * @param keyEvent Reference to key event.
     *
     * @return True if event is consumed, false otherwise.
     */
    virtual bool
    consumeKeyEvent(const KeyEvent& keyEvent);

    /*!
     * Returns current stylist.
     *
     * @sa Stylist
     */
    static Stylist* const
    stylist();

    /*!
     * Returns the pointer to the parent widget.
     * NULL if widget has no parent.
     */
    Widget*
    parent() const;

    /*!
     * Returns the pointer to widget's surface.
     */
    Surface*
    surface() const;

    /*!
     * Set the surface description for widget's surface.
     *
     * \warning Initialise flag must be set to true.
     */
    void
    setSurfaceFlags(SurfaceDescription desc);

    /*!
     * Returns event manager of widget.
     */
    EventManager*
    eventManager() const;

    /*!
     * This signal is emitted before widget is painted only if its geometry is modified.
     * By default widget's updateFrameGeometry() method is connected to this signal.
     */
    sigc::signal<void> sigGeometryUpdated;

  protected:
    /*!
     * This property holds widget's current state, e.g. Pressed or Exposed. It is set to DefaultState by default.
     */
    WidgetState _state;

    /*!
     * This property controls the allocation of widget's surface and specifies how its
     * frame and surface geometry should be used. It is set to DefaultDescription by default.
     */
    SurfaceDescription _surfaceDesc;

    /*!
     * This property stores widget's input capabilities. It is set to NoInput by default.
     */
    WidgetInputMethod _inputMethod;

    /*!
     * This property stores widget's relative position (x, y) inside its parent.
     */
    Point _surfaceGeometry;

    /*!
     * This property stores widget's absolute position (x, y) and surface dimension.
     *
     * Primary use of frame geometry is to determine if a pointer event should be consumed by the widget.
     * If x and y coordinates of an event are inside a widget's frane geometry, event is consumed and the widget's input
     * event handlers are executed accordingly.
     *
     * Note that if the event coordinates are contained by more than one widget, events
     * are consumed by widget which is on top.
     */
    Rectangle _frameGeometry;

    // Fixme remove these types?
    typedef std::list<Widget*> WidgetList;
    typedef WidgetList::iterator WidgetListIterator;
    typedef WidgetList::const_iterator WidgetListConstIterator;
    typedef WidgetList::reverse_iterator WidgetListReverseIterator;
    typedef WidgetList::const_reverse_iterator WidgetListConstReverseIterator;

    //! This list holds the children of the widget.
    WidgetList _children;

    /*!
     * Returns true if widget is a child.
     */
    bool
    isChild(Widget* child);

    /*!
     * Adds a child to this widget. The child is owned by widget.
     *
     * Returns true if successful.
     *
     * @param child widget.
     */
    bool
    addChild(Widget* child);

    /*!
     * If given widget is a child, deletes widget and removes it from children list.
     *
     * Returns true if successful.
     *
     * @param child widget.
     */
    bool
    removeChild(Widget* child);

    /*!
     * Puts the child on the front of the children list.
     *
     * Returns true if successful.
     *
     * @param child of this widget.
     */
    bool
    raiseChildToFront(Widget* child);

    /*!
     * Puts the child on the back of the children list.
     *
     * @param child of this widget.
     */
    bool
    lowerChildToBottom(Widget* child);

    /*!
     * Raises the child by one within the children list.
     *
     * @param child of this widget.
     */
    bool
    raiseChild(Widget* child);

    /*!
     * Lowers the child by one within the children list.
     *
     * @param child of this widget.
     */
    bool
    lowerChild(Widget* child);

    /*!
     * Paints children.
     *
     * @param rect bounding rectangle in absolute coordinates.
     */
    virtual void
    paintChildren(const Rectangle& rect);

    /*!
     * This method is called within widget's paint method in order to initialise or
     * modify widget's surface and update the geometry of widget's frame and children.
     */
    void
    updateSurface();

    /*!
     * This method updates widget's absolute geometry and it is called when
     * sigGeometryUpdated is triggered.
     */
    virtual void
    updateFrameGeometry();

    /*!
     * Draws a widget on its surface.
     *
     * Reimplement this method in derived classes.
     */
    virtual void
    compose()=0;

    /*!
     * This method is called if a key is pressed while the widget has focus.
     *
     * If you are developing a widget for RC use, you should implement this method
     * instead of keyUpEvent().
     *
     * @param keyEvent
     */
    virtual void
    keyDownEvent(const KeyEvent& keyEvent);

    /*!
     * This method is called if a key is released while the widget has focus.
     *
     * @param keyEvent
     */
    virtual void
    keyUpEvent(const KeyEvent& keyEvent);

    /*!
     * This method is called if pointer's button is pressed over widget.
     *
     * @param pointerEvent
     */
    virtual void
    pointerButtonDownEvent(const PointerEvent& pointerEvent);

    /*!
     * This method is called if pointer's button is released over widget.
     *
     * @param pointerEvent
     */
    virtual void
    pointerButtonUpEvent(const PointerEvent& pointerEvent);

    /*!
     * This method is called if widget is grabbed.
     *
     * Note: Only widgets with pointer tracking can be grabbed.
     */
    virtual void
    pointerGrabEvent(const PointerEvent& pointerEvent);

    /*!
     * This method is called once widget is no longer grabbed.
     *
     * Note: Only widgets with pointer tracking can be grabbed.
     */
    virtual void
    pointerReleaseEvent(const PointerEvent& pointerEvent);

    /*!
     * This method is called every time the pointer is moved over widget.
     *
     * @param pointerEvent
     */
    virtual void
    pointerMotionEvent(const PointerEvent& pointerEvent);

    /*!
     * This method is called if pointer's wheel is rotated over widget.
     *
     * @param pointerEvent
     */
    virtual void
    pointerWheelEvent(const PointerEvent& pointerEvent);

    /*!
     * This method is called when widget receives key input focus.
     */
    virtual void
    focusInEvent();

    /*!
     * This method is called when widget loses key input focus.
     */
    virtual void
    focusOutEvent();

    /*!
     * This method is called when pointer enters widget's surface.
     *
     * @param pointerEvent
     */
    virtual void
    enterEvent(const PointerEvent& pointerEvent);

    /*!
     * This method is called when pointer leaves widget's surface.
     *
     * @param pointerEvent
     */
    virtual void
    leaveEvent(const PointerEvent& pointerEvent);

    /*!
     * Sets widget's SurfaceModified geometry flag.
     */
    void
    setSurfaceGeometryModified();

  private:
    //! This property stores the widget's opacity.
    u8 _opacity;
    //! This property stores the widget's parent.
    Widget* _parent;
    //! This property stores the widget's surface.
    Surface* _surface;
    //! This property stores the window of widget.
    WindowWidget* _rootWindow;

    //! This property stores the previously selected child, if any, inside this widget.
    Widget* _preSelectedWidget;
    //! This property stores widgets around this widget.
    Widget* _neighbours[4];

    //! This property defines widget's behaviour inside a layout. Default is NoConstraint.
    WidgetResizeConstraint _xResizeConstraint;
    //! This property defines widget's behaviour inside a layout. Default is NoConstraint.
    WidgetResizeConstraint _yResizeConstraint;

    //! This property holds the widget's minimum allowed size that is specified by the user.
    /*!
     * Note that minimum size overrides layout resize constraints.
     *
     * In order to set a minimum size use setMinimumSize() member method. If you wish to
     * disable minimum size for width or height use 0 for that value.
     */
    Size _minSize;

    //! This property holds the widget's maximum allowed size that is specified by the user.
    /*!
     * Note that maximum size overrides layout resize constraints.
     *
     * In order to set a maximum size use setMaximumSize() member method. If you wish to
     * disable maximum size for width or height use 0 for that value.
     */
    Size _maxSize;

    //! Pointer to application wide Stylist instance.
    /*!
     * The stylist is set and maintained by the main application. It is used for acquiring default
     * size hints and drawing widgets according to a particular style.
     *
     * @sa Application::setStylist()
     */
    static Stylist* _stylist;

    /*!
     * Attaches widget to given root window.
     *
     * This method is used by window widgets upon initialisation.
     *
     * @param rootWindow that this widget belongs to.
     */
    void
    setRootWindow(WindowWidget* rootWindow);

    /*!
     * Deletes surface and unsets InitialiseSurface flag.
     *
     * Must be executed by root window, if window surface is released.
     */
    void
    invalidateSurface();
  };
}

#endif /* ILIXI_WIDGET_H_ */
