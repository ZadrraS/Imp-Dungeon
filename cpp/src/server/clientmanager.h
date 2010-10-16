#ifndef IMPDUNGEON_SERVER_CLIENTMANAGER_H_
#define IMPDUNGEON_SERVER_CLIENTMANAGER_H_

#include <netinet/in.h>
#include <stdint.h>
#include <sys/types.h>
#include <vector>

#include <boost/uuid/uuid.hpp>
#include <boost/unordered_map.hpp>

namespace impdungeon {
namespace server {

class ClientManager {
 public:
  ClientManager();
  virtual ~ClientManager();

  void AddClient(int descriptor);
  void RemoveClient(int descriptor);

  boost::uuids::uuid GetClientId(int descriptor);
  void RegisterClient(int descriptor, const boost::uuids::uuid &id);

  bool HasClient(int descriptor);
  bool IsClientRegistered(int descriptor);

  fd_set CopyClientDescriptors() const;

  int max_descriptor() const;

  std::vector<int>::iterator begin();
  std::vector<int>::iterator end();
  typedef std::vector<int>::iterator iterator;
  typedef std::vector<int>::const_iterator const_iterator;

 private:
  boost::unordered_map<int, boost::uuids::uuid> client_ids_; 
  std::vector<int> client_list_;
  fd_set client_descriptors_;
  int max_descriptor_;
};

}  // namespace server
}  // namespace impdungeon

#endif  // IMPDUNGEON_SERVER_CLIENTMANAGER_H_
