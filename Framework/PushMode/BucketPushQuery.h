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

#include "../HttpQueries/IHttpQuery.h"
#include "../OrthancInstancesCache.h"

namespace OrthancPlugins
{
  class BucketPushQuery : public IHttpQuery
  {
  private:
    OrthancInstancesCache&  cache_;
    TransferBucket          bucket_;
    std::string             peer_;
    std::string             uri_;
    BucketCompression       compression_;

  public:
    BucketPushQuery(OrthancInstancesCache& cache,
                    const TransferBucket& bucket,
                    const std::string& peer,
                    const std::string& transactionUri,
                    size_t bucketIndex,
                    BucketCompression compression);

    virtual Orthanc::HttpMethod GetMethod() const
    {
      return Orthanc::HttpMethod_Put;
    }

    virtual const std::string& GetPeer() const
    {
      return peer_;
    }

    virtual const std::string& GetUri() const
    {
      return uri_;
    }

    virtual void ReadBody(std::string& body) const;

    virtual void HandleAnswer(const void* answer,
                              size_t size);
  };
}
