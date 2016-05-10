# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

def after_scenario(context, scenario):
	if hasattr(context, 'application'):
		context.application.terminate()
		context.application.wait()
	if hasattr(context, 'dbus'):
		context.dbus.terminate()
		context.dbus.wait()
	if hasattr(context, 'mqtt'):
		context.mqtt.cleanup()

