/*
  ==============================================================================

   This file is part of the JUCE 6 technical preview.
   Copyright (c) 2020 - Raw Material Software Limited

   You may use this code under the terms of the GPL v3
   (see www.gnu.org/licenses).

   For this technical preview, this file is not subject to commercial licensing.

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

namespace juce
{

/** @internal */
bool juce_handleXEmbedEvent (ComponentPeer*, void*);
/** @internal */
unsigned long juce_getCurrentFocusWindow (ComponentPeer*);

#if JUCE_LINUX || DOXYGEN

//==============================================================================
/**
    A Linux-specific class that can embed a foreign X11 widget.

    Use this class to embed a foreign X11 widget from other toolkits such as
    GTK+ or QT.

    There are two ways to initiate the Xembed protocol. Either the client creates
    a window and passes this to the host (client initiated) or the host
    creates a window in which the client can reparent it's client widget
    (host initiated). XEmbedComponent supports both protocol types.

    This is how you embed a GTK+ widget: if you are using the client
    initiated version of the protocol, then create a new gtk widget with
    gtk_plug_new (0). Then query the window id of the plug via gtk_plug_get_id().
    Pass this id to the constructor of this class.

    If you are using the host initiated version of the protocol, then first create
    the XEmbedComponent using the default constructor. Use getHostWindowID to get
    the window id of the host, use this to construct your gtk plug via gtk_plug_new.

    A similar approach can be used to embed QT widgets via QT's QX11EmbedWidget
    class.

    Other toolkits or raw X11 widgets should follow the X11 embed protocol:
    https://specifications.freedesktop.org/xembed-spec/xembed-spec-latest.html

    @tags{GUI}
*/
class XEmbedComponent : public Component
{
public:
    //==============================================================================

    /** Creates a JUCE component wrapping a foreign widget

        Use this constructor if you are using the host initiated version
        of the XEmbedProtocol. When using this version of the protocol
        you must call getHostWindowID() and pass this id to the foreign toolkit.
    */
    XEmbedComponent (bool wantsKeyboardFocus = true,
                     bool allowForeignWidgetToResizeComponent = false);

    /** Create a JUCE component wrapping the foreign widget with id wID

        Use this constructor if you are using the client initiated version
        of the XEmbedProtocol.
    */
    XEmbedComponent (unsigned long wID, bool wantsKeyboardFocus = true,
                     bool allowForeignWidgetToResizeComponent = false);


    /** Destructor. */
    ~XEmbedComponent() override;

    /** Use this method to retrieve the host's window id when using the
        host initiated version of the XEmbedProtocol
    */
    unsigned long getHostWindowID();

    /** Removes the client window from the host. */
    void removeClient();

protected:
    //==============================================================================
    /** @internal */
    void paint (Graphics&) override;
    void focusGained (FocusChangeType) override;
    void focusLost (FocusChangeType) override;
    void broughtToFront() override;

private:
    friend bool juce::juce_handleXEmbedEvent (ComponentPeer*, void*);
    friend unsigned long juce_getCurrentFocusWindow (ComponentPeer*);

    class Pimpl;
    std::unique_ptr<Pimpl> pimpl;
};

#endif

} // namespace juce
