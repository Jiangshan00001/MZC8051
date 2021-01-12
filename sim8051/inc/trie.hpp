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

#ifndef _TRIE_HPP
#define _TRIE_HPP

#include <string>
#include <map>

class TrieNode
{
  public:
    TrieNode();
    TrieNode(TrieNode *parent);
    std::map<char, TrieNode*> edges;
    bool isString;
    TrieNode *parent;
};

class Trie
{
  private:
    TrieNode root;
    TrieNode *current;
  public:
    /*
     * Constructor.
     */
    Trie();
    /*
     * Resets the traversal state to the root node
     */
    void Reset();
    /*
     * Changes the traversal state to the previous node
     */
    void RemoveChar();
    /*
     * Checks if there is an outgoing edge from the current node that matches 'c'.
     * Returns 'true' if there is an edge, 'false' if not.
     */
    bool AddChar(char c);
    /*
     * Traverses the trie as long as there is a unique path from the current node.
     * Stops when there is more than one outgoing edge or a complete string is found.
     * Returns a string consisting of the characters on the edges.
     */
    std::string Traverse();
    /*
     * Returns true if the current traversal state matches a string, false if not
     */
    bool IsString();
    /*
     * Adds the string 's' to the trie.
     */
    void AddString(std::string s);
};

#endif
