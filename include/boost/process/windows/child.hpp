// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_CHILD_HPP
#define BOOST_PROCESS_WINDOWS_CHILD_HPP

#include <boost/move/move.hpp>
#include <boost/detail/winapi/handles.hpp>
#include <boost/detail/winapi/process.hpp>

namespace boost { namespace process { namespace windows {

struct child_handle
{
    ::boost::detail::winapi::PROCESS_INFORMATION_ proc_info;

    explicit child_handle(const ::boost::detail::winapi::PROCESS_INFORMATION_ &pi) : proc_info(pi) {}

    ~child_handle()
    {
        ::boost::detail::winapi::CloseHandle(proc_info.hProcess);
        ::boost::detail::winapi::CloseHandle(proc_info.hThread);
    }
    child_handle(const child_handle & c) = delete;
    child_handle(child_handle && c) : proc_info(c.proc_info)
    {
        c.proc_info.hProcess = ::boost::detail::winapi::invalid_handle_value;
        c.proc_info.hThread  = ::boost::detail::winapi::invalid_handle_value;
    }
    child_handle &operator=(const child_handle & c) = delete;
    child_handle &operator=(child_handle && c)
    {
        ::boost::detail::winapi::CloseHandle(proc_info.hProcess);
        ::boost::detail::winapi::CloseHandle(proc_info.hThread);
        proc_info = c.proc_info;
        c.proc_info.hProcess = ::boost::detail::winapi::invalid_handle_value;
        c.proc_info.hThread  = ::boost::detail::winapi::invalid_handle_value;
        return *this;
    }

    int get_pid() const
    {
        return static_cast<int>(proc_info.dwProcessId);
    }

    typedef ::boost::detail::winapi::HANDLE_ process_handle_t;
    process_handle_t process_handle() const { return proc_info.hProcess; }

};

}}}

#endif