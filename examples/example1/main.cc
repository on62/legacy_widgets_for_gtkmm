/* Copyright (c) 2019  Thomas Erbesdobler <t.erbesdobler@gmx.de>
 *
 * This file is part of legacy_widgets_for_gtkmm.
 *
 * legacy_widgets_for_gtkmm is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 2.1 of the License,
 * or (at your option) any later version.
 *
 * legacy_widgets_for_gtkmm is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtkmm/application.h>
#include "LWGExampleWindow.h"

int main(int argc, char **argv)
{
	auto app = Gtk::Application::create (argc, argv, "gmx.erbesdobler.t.lwgexample");

	LWGExampleWindow w;

	return app->run (w);
}
