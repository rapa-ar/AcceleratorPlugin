/**
 * Transfers accelerator plugin for Orthanc
 * Copyright (C) 2018-2021 Osimis S.A., Belgium
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 **/


#pragma once

#include "HttpQueriesQueue.h"

#include <boost/thread.hpp>


namespace OrthancPlugins
{
  class HttpQueriesRunner : public boost::noncopyable
  {
  private:
    HttpQueriesQueue&            queue_;
    std::vector<boost::thread*>  workers_;
    bool                         continue_;
    boost::posix_time::ptime     start_;

    boost::mutex                 mutex_;
    size_t                       totalTraffic_;
    boost::posix_time::ptime     lastUpdate_;

    static void Worker(HttpQueriesRunner* that);

  public:
    HttpQueriesRunner(HttpQueriesQueue& queue,
                      size_t threadsCount);

    ~HttpQueriesRunner();

    void GetSpeed(float& kilobytesPerSecond);
  };
}
