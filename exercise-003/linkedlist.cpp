#include "linkedlist.h"

LinkedList::~LinkedList()
{
  for (auto tmp = m_head; tmp != nullptr; tmp = tmp->pNext /* prepare the next in the row */) {
    auto elem = tmp; /* save the element to be deleted */
    delete elem;
  }
}

bool LinkedList::insert_tail(LinkedListNode *node)
{
  bool ret = false;
  if (nullptr == node) {
    return ret;
  }

  //ab hier coden:
  if (nullptr == m_head) {
    m_head = m_tail = node;
  } else {
    m_tail->pNext = node;
    m_tail = node;
  }

  ret = true;
  return ret;
}


bool LinkedList::insert_head(LinkedListNode *node)
{
  bool ret = false;
  if (nullptr == node) {
    return ret;
  }
  //ab hier coden:
  node->pNext = m_head;
  m_head = node;

  if (nullptr == m_tail) {
    m_tail = node;
  }

  ret = true;
  return ret;
}


bool LinkedList::insert_after(LinkedListNode *loc, LinkedListNode *node)
{
  bool ret = false;
  if ((nullptr == loc) || (nullptr == node)) {
    return ret;
  }

  node->pNext = loc->pNext;
  loc->pNext = node;

  if (loc == m_tail) {
    m_tail = node;
  }

  ret = true;
  return ret;
}


bool LinkedList::insert_before(LinkedListNode *loc, LinkedListNode *node)
{
  bool ret = false;
  if ((nullptr == loc) || (nullptr == node)) {
    return ret;
  }

  if (loc == m_head) {
    return insert_head(node);
  }

  auto tmp = m_head;
  while (tmp != nullptr && tmp->pNext != loc) {
    tmp = tmp->pNext;
  }

  if (tmp == nullptr) {
    return false;
  }

  node->pNext = loc;
  tmp->pNext = node;

  ret = true;
  return ret;
}


bool LinkedList::remove(LinkedListNode *node)
{
  bool ret = false;
  if (node == nullptr || m_head == nullptr) {
    return ret;
  }

  if (node == m_head) {
    m_head = m_head->pNext;
    if (m_head == nullptr) {
      m_tail = nullptr;
    }
    delete node;
    ret = true;
    return ret;
  }

  auto tmp = m_head;
  while (tmp != nullptr && tmp->pNext != node) {
    tmp = tmp->pNext;
  }

  if (tmp == nullptr) {
    return false;
  }

  tmp->pNext = node->pNext;
  if (node == m_tail) {
    m_tail = tmp;
  }

  delete node;
  ret = true;
  return ret;
}


size_t LinkedList::size()
{
  size_t count = 0;
  /* using a lambda to count objects in the list*/
  traverse([&count](LinkedListNode *node) { count++; });
  return count;
}


void LinkedList::traverse(std::function<void(const std::string &)> func)
{
  traverse([&](LinkedListNode *node) { func(node->m_name); });
}

void LinkedList::traverse(std::function<void(LinkedListNode *node)> func)
{
  for (auto tmp = m_head; tmp != nullptr; tmp = tmp->pNext) {
    func(tmp);
  }
}