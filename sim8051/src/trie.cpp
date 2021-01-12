/*
 * Copyright (C) 2016 Sensative AB
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "trie.hpp"
#include <map>

TrieNode::TrieNode() : isString(false), parent(nullptr)
{
}

TrieNode::TrieNode(TrieNode *p) : isString(false), parent(p)
{
}

Trie::Trie() : current(&root)
{
}

void Trie::Reset()
{
  current = &root;
}

void Trie::RemoveChar()
{
  if (current != &root)
  {
    current = current->parent;
  }
}

bool Trie::AddChar(char c)
{
  if (current->edges.find(c) != current->edges.end())
  {
    current = current->edges[c];
    return true;
  }
  else
  {
    return false;
  }
}

std::string Trie::Traverse()
{
  std::string s;

  while (!current->isString && current->edges.size() == 1)
  {
    std::map<char, TrieNode*>::iterator i = current->edges.begin();
    s += i->first;
    current = i->second;
  }

  return s;
}

bool Trie::IsString()
{
  return current->isString;
}

void Trie::AddString(std::string s)
{
  TrieNode *node = &root;

  for (int i = 0; i < s.length(); i++)
  {
    std::map<char, TrieNode*>::iterator it = node->edges.find(s[i]);
    if (it == node->edges.end())
    {
      TrieNode *newNode = new TrieNode(node);
      node->edges[s[i]] = newNode;
      node = newNode;
    }
    else
    {
      node = it->second;
    }
  }
  node->isString = true;
}
