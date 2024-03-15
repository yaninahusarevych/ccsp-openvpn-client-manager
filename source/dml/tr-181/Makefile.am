##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2024 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################

AM_CPPFLAGS = -I=${includedir} 

AM_CFLAGS = -D_ANSC_LINUX -D_ANSC_USER -D_ANSC_LITTLE_ENDIAN_ $(DBUS_CFLAGS)

AM_LDFLAGS = -lccsp_common $(DBUS_LIBS)

test_component_SOURCES = cosa_apis_testcomponentplugin.c 
