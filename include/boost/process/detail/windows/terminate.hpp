// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_TERMINATE_HPP
#define BOOST_PROCESS_WINDOWS_TERMINATE_HPP

#include <boost/process/config.hpp>
#include <boost/system/error_code.hpp>
#include <cstdlib>
#include <boost/detail/winapi/process.hpp>
#include <boost/detail/winapi/get_last_error.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

inline void terminate(const child_handle &p)
{
    if (!::boost::detail::winapi::TerminateProcess(p.process_handle(), EXIT_FAILURE))
        boost::process::detail::throw_last_error("TerminateProcess() failed");
}

inline void terminate(const child_handle &p, std::error_code &ec)
{
    if (!::boost::detail::winapi::TerminateProcess(p.process_handle(), EXIT_FAILURE))
        ec = boost::process::detail::get_last_error();
    else
        ec.clear();
}

}}}}

#endif