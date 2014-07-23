#!/usr/bin/env python
from __future__ import print_function

import dbus
from dbus.mainloop.glib import DBusGMainLoop

DBusGMainLoop(set_as_default=True)

import gobject

loop = gobject.MainLoop()

srv_addr = 'unix:path=/run/user/1000/pulse/dbus-socket'
bus=dbus.connection.Connection(srv_addr)


core = bus.get_object(object_path='/org/pulseaudio/core1')
sinks = ( dbus.Interface( bus.get_object(object_path=path),
          dbus_interface='org.freedesktop.DBus.Properties' ) for path in bus\
        .get_object(object_path='/org/pulseaudio/core1').Get(
          'org.PulseAudio.Core1', 'Sinks', dbus_interface='org.freedesktop.DBus.Properties' ) )

sinks_list = [s for s in sinks]

sink=sinks_list[1]

def volume_updated_callback(*args, **kwargs):
  vol, vol2 = (args[0][0], args[0][1])
  print('VolumeUpdated : ' + str(vol) + ' (' + str(vol2) + ')')

def mute_updated_callback(*args, **kwargs):
  muted = args[0]
  text = 'Muted' if muted else 'Unmuted'

  print('MuteUpdated : ' + text)


names_and_handlers=[
  ("VolumeUpdated", volume_updated_callback),
  ("MuteUpdated", mute_updated_callback)
  ]

for sig_name, sig_handler in names_and_handlers:
  bus.add_signal_receiver(sig_handler, sig_name)
  core.ListenForSignal('org.PulseAudio.Core1.Device.{}'.format(sig_name),
    dbus.Array(['/org/pulseaudio/core1/sink1'], signature='o'))

print(str(sink.Get( 'org.PulseAudio.Core1.Device', 'Volume',
          dbus_interface='org.freedesktop.DBus.Properties' )[0]))

sink.Set( 'org.PulseAudio.Core1.Device', 'Volume', [dbus.UInt32(5000),dbus.UInt32(5000)],
          dbus_interface='org.freedesktop.DBus.Properties' )

sink.Set( 'org.PulseAudio.Core1.Device', 'Volume', [dbus.UInt32(4000),dbus.UInt32(4000)],
          dbus_interface='org.freedesktop.DBus.Properties' )

sink.Set( 'org.PulseAudio.Core1.Device', 'Mute', dbus.Boolean(False),
          dbus_interface='org.freedesktop.DBus.Properties' )

sink.Set( 'org.PulseAudio.Core1.Device', 'Mute', dbus.Boolean(True),
          dbus_interface='org.freedesktop.DBus.Properties' )

print(str(sink.Get( 'org.PulseAudio.Core1.Device', 'Volume',
          dbus_interface='org.freedesktop.DBus.Properties' )[0]))


loop.run()

print(str(sink.Get( 'org.PulseAudio.Core1.Device', 'Volume',
          dbus_interface='org.freedesktop.DBus.Properties' )[0]))




