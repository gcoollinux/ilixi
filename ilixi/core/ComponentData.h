#ifndef ILIXI_COMPONENTDATA_H_
#define ILIXI_COMPONENTDATA_H_

#include <directfb.h>

#ifdef __cplusplus
namespace ilixi
{
//****************************************************************************
// ilixi::OSK (On-Screen-Keyboard)
//****************************************************************************
namespace OSK
{
#endif
/*!
 * This enum is used to specify the layout for OSK application.
 */
typedef enum
{
    Standard,   //!< This layout has letters, numbers and symbols. It is the default one.
    Numeric,    //!< This layout has numbers only.
    URL         //!< This layout has letters, numbers and symbols for valid URLs.
} OSKLayoutMode;

/*!
 * This structure is used for making a request to OSK component by client applications.
 */
typedef struct
{
    DFBRectangle inputRect; //!< This is the bounding box around the target input widget.
    OSKLayoutMode mode;     //!< This specifies the OSK layout.
    pid_t client;           //!< PID of the client application.
} OSKRequest;

/*!
 * This enum specifies the COMA methods for OSK component.
 */
typedef enum
{
    ShowOSK,    //!< Show OSK for client application, if hidden.
    HideOSK,    //!< Hide OSK for client application, if showing.
    ConsumeKey  //!< Used by OSK application to send pressed key.
} OSKMethodID;
#ifdef __cplusplus
} /* namespace OSK */
#endif
//****************************************************************************
// ilixi::SoundMixer
//****************************************************************************
#ifdef __cplusplus
namespace SoundMixer
{
#endif
/*!
 * This enum specifies the COMA methods for SoundMixer component.
 */
typedef enum
{
    SetVolume,  //!< Set volume using argument.
    ToggleMute  //!< Toggle Mute.
} SoundMixerMethodID;

/*!
 * This enum specifies the COMA notifications for SoundMixer component.
 */
typedef enum
{
    VolumeChanged = 0,  //!< VolumeChanged
    SMNumNotifications
} SoundMixerNotificationID;
#ifdef __cplusplus
} /* namespace SoundMixer */
#endif
//****************************************************************************
// ilixi::Compositor
//****************************************************************************
#ifdef __cplusplus
namespace Compositor
{
#endif
/*!
 * This structure contains for AppList notifications.
 * e.g. send the list of registered applications to client.
 */
typedef struct
{
    char name[64];  //!< Application's display name.
    char icon[256]; //!< Path for icon.
} AppData;

/*!
 * This structure contains data for Visibilty notifications.
 * e.g. client is notified when it is hidden.
 */
typedef struct
{
    bool multi;     //!< True if application can have multiple instances.
    bool visible;   //!< True if visible, false otherwise.
    char name[64];  //!< Registered name of application.
    pid_t pid;      //!< Target client PID.
} VisibilityData;

/*!
 * This structure contains data for Notification.
 * e.g. Twitter.
 */
typedef struct
{
    char body[128];     //!< Body text.
    char icon[256];     //!< Path for icon.
    char title[128];    //!< Title.
    pid_t client;       //!< PID of client application.
} NotificationData;

/*!
 * This enum specifies the COMA methods for Compositor component.
 */
typedef enum
{
    AddNotification,    //!< Add notification using "NotificationData" as argument.
    GetAppList,         //!< Send list of registered applications to client.
    HideDashboard,      //!< Hide Dashboard application.
    HideHome,           //!< Hide Home application.
    HideSoundMixer,     //!< Hide SoundMixer application.
    HideSwitcher,       //!< Hide Switcher.
    SendBackKey,        //!< Send DIKS_BACK key to currently visible application.
    SetOptions,         //!< Set Compositor options using null terminated XML data.
    ShowDashboard,      //!< Show Dashboard application.
    ShowHome,           //!< Show Home application.
    ShowSoundMixer,     //!< Show SoundMixer application.
    ShowSwitcher,       //!< Show Switcher.
    StartApp            //!< Start application using "char name[64]" as argument.
} CompositorMethodID;

/*!
 * This enum specifies the COMA notifications for Compositor component.
 */
typedef enum
{
    AppStarting = 0,    //!< Sent when an application starts.
    AppVisibilty,       //!< Sent when an application becomes hidden or visible.
    BackKeyHidden,      //!< Sent if BACK key should become hidden.
    BackKeyVisible,     //!< Sent if BACK key should become visible.
    SendingAppList,     //!< Sent with application list. // TODO remove this!
    SwitcherHidden,     //!< Sent when Switcher is hidden.
    SwitcherVisible,    //!< Sent when Switcher is visible.
    CNumNotifications
} CompositorNotifications;
#ifdef __cplusplus
} /* namespace Compositor */
#endif
//****************************************************************************
// ilixi::StatusBar
//****************************************************************************
#ifdef __cplusplus
namespace StatusBar
{
#endif
/*!
 * This enum specifies the COMA methods for StatusBar component.
 */
typedef enum
{
    AddContent,     //!< Adds a remote surface to StatusBar; ContentAdded is sent if successful.
    RemoveContent   //!< Removes a remote surface from StatusBar; ContentRemoved is sent if successful.
} StatCompMethods;

/*!
 * This enum specifies the COMA notifications for StatusBar component.
 */
typedef enum
{
    ContentAdded,   //!< Sent when a remote surface is added.
    ContentRemoved, //!< Sent when a remote surface is removed.
    SBNumNotifications
} StatCompNotifications;
#ifdef __cplusplus
} /* namespace StatusBar */

} /* namespace ilixi */
#endif
#endif /* ILIXI_OSKCOMPONENT_H_ */