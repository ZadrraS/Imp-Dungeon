#include "server/clientmanager.h"

namespace impdungeon {
namespace server {

ClientManager::ClientManager() : max_descriptor_(-1) {
  FD_ZERO(&client_descriptors_);
}

ClientManager::~ClientManager() {

}

void ClientManager::AddClient(int descriptor) {
  FD_SET(descriptor, &client_descriptors_);
  client_list_.push_back(descriptor);

  if (descriptor > max_descriptor_)
    max_descriptor_ = descriptor;
}

void ClientManager::RemoveClient(int descriptor) {
  FD_CLR(descriptor, &client_descriptors_);
  client_list_.erase(std::remove(client_list_.begin(), client_list_.end(),
                                 descriptor), client_list_.end());

  if (client_ids_.count(descriptor) > 0) {
    client_ids_.erase(descriptor);
  }
}

boost::uuids::uuid ClientManager::GetClientId(int descriptor) {
  // TODO(ZadrraS): Make this not explode when handed a bad descriptor.
  return client_ids_[descriptor];
}

void ClientManager::RegisterClient(int descriptor, const boost::uuids::uuid &id) {
  if (std::find(client_list_.begin(), client_list_.end(), descriptor) !=
      client_list_.end()) {
    client_ids_[descriptor] = id;
  }
}

bool ClientManager::HasClient(int descriptor) {
  if (std::find(client_list_.begin(), client_list_.end(), descriptor) !=
      client_list_.end() && FD_ISSET(descriptor, &client_descriptors_)) {
    return true;
  }
  return false;
}

bool ClientManager::IsClientRegistered(int descriptor) {
  if (HasClient(descriptor) && client_ids_.count(descriptor) > 0)
    return true;

  return false;
}

fd_set ClientManager::CopyClientDescriptors() const {
  return client_descriptors_;
}

int ClientManager::max_descriptor() const {
  return max_descriptor_;
}

std::vector<int>::iterator ClientManager::begin() {
  return client_list_.begin();
}

std::vector<int>::iterator ClientManager::end() {
  return client_list_.end();
}

}  // namespace server
}  // namespace impdungeon
