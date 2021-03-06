#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# Copyright (c) 2014-2015, Kevin Läufer
# Copyright (c) 2016, Daniel Krebs
# Copyright (c) 2018, 2020, Niklas Hauser
#
# This file is part of the modm project.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
# -----------------------------------------------------------------------------

from SCons.Script import *
from os.path import join, dirname, abspath
from modm_tools import info

TEMPLATE_SOURCE = join(dirname(abspath(__file__)), "info.c.in")

def git_info_defines(env, with_status=False):
	information = info.git_info(env.Dir("#").abspath)
	if with_status:
		information.update(info.git_status(env.Dir("#").abspath))

	defines = {"MODM_GIT_INFO": 1}
	if with_status: defines["MODM_GIT_STATUS"] = 1
	env.AppendUnique(CPPDEFINES=defines)

	target = join(env["BASEPATH"], "src", "info_git.c")
	subs = {"type": "git", "defines": information}
	sources = env.Jinja2Template(target=target, source=TEMPLATE_SOURCE, substitutions=subs)

	return sources


def build_info_defines(env):
	information = info.build_info(env.Dir("#").abspath, env["CXX"])

	defines = {"MODM_BUILD_INFO": 1}
	env.AppendUnique(CPPDEFINES=defines)

	information["MODM_BUILD_PROJECT_NAME"] = env.get('CONFIG_PROJECT_NAME', 'Unknown')
	target = join(env["BASEPATH"], "src", "info_build.c")
	subs = {"type": "build", "defines": information}
	sources = env.Jinja2Template(target=target, source=TEMPLATE_SOURCE, substitutions=subs)

	return sources


def generate(env, **kw):
	env.AddMethod(git_info_defines, "InfoGit")
	env.AddMethod(build_info_defines, "InfoBuild")

def exists(env):
	return True
