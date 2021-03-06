/*
    Copyright (c) 2007-2014 Contributors as noted in the AUTHORS file

    This file is part of 0MQ.

    0MQ is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    0MQ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __ZMQ_I_ENGINE_HPP_INCLUDED__
#define __ZMQ_I_ENGINE_HPP_INCLUDED__

#include "fd.hpp"

namespace zmq
{

    class io_thread_t;

    //  Abstract interface to be implemented by various engines.

    struct i_engine
    {
        virtual ~i_engine () {}

        //  Plug the engine to the session.
        virtual void plug (zmq::io_thread_t *io_thread_,
            class session_base_t *session_) = 0;

        //  Terminate and deallocate the engine. Note that 'detached'
        //  events are not fired on termination.
        virtual void terminate () = 0;

        //  This method is called by the session to signalise that more
        //  messages can be written to the pipe.
        virtual void restart_input () = 0;

        //  This method is called by the session to signalise that there
        //  are messages to send available.
        virtual void restart_output () = 0;

        virtual void zap_msg_available () = 0; 
        
        // provide a way to link from engine to file descriptor 
        virtual fd_t get_assoc_fd () { return retired_fd;};
    };

}

#endif
