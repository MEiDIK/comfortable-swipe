#ifndef __COMFORTABLE_SWIPE__gesture_mouse_swipe_gesture__
#define __COMFORTABLE_SWIPE__gesture_mouse_swipe_gesture__

/*
Comfortable Swipe
by Rico Tiongson

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream> // std::cout, std::endl
#include <cstdio> // std::sscanf
#include "mouse_swipe_gesture.h"

extern "C"
{
    #include <xdo.h> // xdo, xdo_new, xdo_free,
                     // xdo_get_mouse_location
                     // CURRENT_WINDOW
}

namespace comfortable_swipe::gesture
{
    /**
     * Constructs a new mouse gesture, given "hold3" and "hold4" configurations.
     */
    mouse_swipe_gesture::mouse_swipe_gesture
    (
        const char* hold3,
        const char* hold4
    ):
        comfortable_swipe::gesture::swipe_gesture(),
        hold3(hold3),
        hold4(hold4),
        flag_mousedown(false)
    { }

    /**
     * Destructs this mouse swipe gesture.
     */
    mouse_swipe_gesture::~mouse_swipe_gesture()
    { }

    /**
     * Run mousedown command on hold input.
     */
    void mouse_swipe_gesture::do_mousedown(const char * mouseinput)
    {
        int mouse = this->parse_mouse_input(mouseinput);
        if (mouse != -1)
        {
            std::cout << "MOUSE DOWN " << mouse << std::endl;
            this->flag_mousedown = true;
        }
    }

    /**
     *
     */
    void mouse_swipe_gesture::do_mouseup(const char * mouseinput)
    {
        int mouse = this->parse_mouse_input(mouseinput);
        if (mouse != -1)
        {
            std::cout << "MOUSE UP " << mouse << std::endl;
            this->flag_mousedown = false;
        }
    }

    /**
     * Utility method to parse mouse number from input.
     * Returns -1 on failure.
     */
    int mouse_swipe_gesture::parse_mouse_input(const char *input)
    {
        // parse mouse number
        int mouseno;
        if (std::sscanf(input, "mouse%d", &mouseno) == 1)
        {
            return mouseno;
        }
        return -1;
    }

    /**
     * Hook on begin of mouse swipe gesture.
     */
    void mouse_swipe_gesture::begin()
    {
        // call superclass method
        swipe_gesture::begin();
        // dispatch mouse down event
        if (this->fingers == 3)
        {
            this->do_mousedown(this->hold3);
        }
        else if (this->fingers == 4)
        {
            this->do_mousedown(this->hold4);
        }
    }

    /**
     * Hook on end of mouse swipe gesture.
     */
    void mouse_swipe_gesture::update()
    {
        // call superclass method
        swipe_gesture::update();
        if (this->is_mousedown())
        {
            // TODO: drag mouse while it's updating
            std::cout << this->dx << " " << this->dy << std::endl;
        }

    }

    /**
     * Hook on end of swipe gesture.
     */
    void mouse_swipe_gesture::end()
    {
        if (this->is_mousedown())
        {
            if (this->fingers == 3)
            {
                this->do_mouseup(this->hold3);
            }
            else if (this->fingers == 4)
            {
                this->do_mouseup(this->hold4);
            }
        }

        // call superclass method
        swipe_gesture::end();
    }

    /**
     * Utility method to check if mouse is current held.
     */
    bool mouse_swipe_gesture::is_mousedown()
    {
        return this->flag_mousedown;
    }
}

#endif /* __COMFORTABLE_SWIPE__gesture_mouse_swipe_gesture__ */
