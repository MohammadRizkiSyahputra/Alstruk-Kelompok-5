#pragma once
#include <iostream>
using namespace std;

struct CSQueueNode
{
    string username;
    string tujuanCS;
    string kcp_code;
    int session_code; // jam, misal 8, 9, dst
    int queue_number;
    int cs_table;
    string queue_id; // contoh: JKT-15-001
    CSQueueNode *next;
};

struct CSQueue
{
    CSQueueNode *head, *tail;
    int count;

    CSQueue()
    {
        head = NULL;
        tail = NULL;
        count = 0;
    }

    void enqueue(string username, string tujuanCS, string kcp_code, int session_code, int cs_table)
    {
        CSQueueNode *node = new CSQueueNode;
        node->username = username;
        node->tujuanCS = tujuanCS;
        node->kcp_code = kcp_code;
        node->session_code = session_code;
        node->cs_table = cs_table;
        node->queue_number = count + 1;
        // Format queue_id: JKT-15-001
        char buf[20];
        sprintf(buf, "%s-%02d-%03d", kcp_code.c_str(), session_code, node->queue_number);
        node->queue_id = buf;
        node->next = NULL;

        if (head == NULL)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
        count++;
    }

    void dequeue()
    {
        if (head == NULL)
            return;
        CSQueueNode *del = head;
        head = head->next;
        delete del;
        count--;
        if (head == NULL)
            tail = NULL;
    }

    void tampil()
    {
        CSQueueNode *bantu = head;
        while (bantu != NULL)
        {
            cout << bantu->queue_id << " | " << bantu->username << " | " << bantu->tujuanCS << " | Meja: " << bantu->cs_table << endl;
            bantu = bantu->next;
        }
    }

    CSQueueNode *findByUsername(string uname)
    {
        CSQueueNode *bantu = head;
        while (bantu != NULL)
        {
            if (bantu->username == uname)
                return bantu;
            bantu = bantu->next;
        }
        return NULL;
    }

    CSQueueNode *getActive()
    {
        return head;
    }
};