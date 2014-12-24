#ifndef __LINK_TOOL_H
#define __LINK_TOOL_H
#include "thread_base.h"
#include <map>
#include <stddef.h>
#include <string>
#include <stdlib.h>


#define TQueueContain(x) container_of((x), ThreadNode, node)
#define each_link_node(head, node) for ((node)=(head)->next; (head) != (node); (node)=(node)->next)
#define TRACE_INF_LEN  512

typedef struct node
{
    struct node *next;
	struct node *pre;
}node;

void init_node(struct node *node);
void insert_node(struct node *node, struct node *inser_node);
void remov_node(struct node *node);

struct  CList
{
public:
	static CList *createCList();
	static void destroyClist(CList *pCList);
public:
	int push_back(node *pNode);
	node *begin();
	node *back();
	void pop_front();
	void pop_back();
	bool empty();
	void clear();
	int size();
	node *getHead();
	node *find(node *cmpNode, bool (*cmpFuc)(node *node1, node *node2));
private:
	void init();
	void exit();
public:
	node head_node;
	node *tail;
	int node_num;
};


typedef struct CStrNode
{
public:
	static CStrNode *createCStrNode(int maxStrLen);
	static void destroyCStrNode(CStrNode *pNode);
public:
	node *getNode();
	int size();
	void setStr(char *str, int strLen = -1);
	char *getStr();
	int writeStr(char *str);
private:
	void init(int maxStrLen);
	void exit();
public:
	struct node m_node;
	char *m_str;
	int m_strLen;
	int m_remainMem;
}CStrNode;
#define TStrNodeContain(x) container_of((x), CStrNode, m_node)

struct CString
{
public:
	static CString* createCString();
	static void  destroyCString(CString *pCString);
public:	
	void append(char *str);
	void append(const char *str);
	char *c_str();
	int size();
	void clear();
private:
	void init();
	void exit();
private:
	CList *m_pStrList;
	CStrNode *m_lastStrNode;
	int m_strLen;
	int m_maxStrNodeLen;
};

class CPthreadMutex
{
public:
	///\brief ���캯����Ĭ��Ϊ������
	CPthreadMutex()
	{
		m_mutex = (base::pthread_mutex_t *)base::malloc(sizeof(base::pthread_mutex_t));
		base::pthread_mutex_init(m_mutex, NULL);
	}

	///\brief ��������
	~CPthreadMutex()
	{
		free(m_mutex);
	}

	///\brief ռ����
	bool Enter()
	{
		base::pthread_mutex_lock(m_mutex);
		return true;
	}

	///\brief �ͷ���
	bool Leave()
	{
		base::pthread_mutex_unlock(m_mutex);
		return true;
	}

private:
	base::pthread_mutex_t  *m_mutex;
};

class CGuardMutex
{
public:
	///\brief ���캯��
	inline CGuardMutex(CPthreadMutex& mutex)
		:m_mutex(mutex)
	{
		m_mutex.Enter();
	};

	///\brief ��������
	inline ~CGuardMutex()
	{
		m_mutex.Leave();
	};
private:
	CPthreadMutex &m_mutex;
};


typedef enum
{
	e_Mem, 
	e_TimeCalc, 
	e_ThreadEnableNum,
}E_ENABLE_TYPE;

typedef struct 
{
	base::pthread_t thread_id;
	bool enable[e_ThreadEnableNum];
	struct node node;
}ThreadNode;





#endif

