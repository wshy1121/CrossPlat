#include "stdafx.h"
#include "link_tool.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

using namespace base;
/******************************************************/
void init_node(struct node *node)
{
	node->next = node;
	node->pre = node;
	return ;
}

//��巨
void insert_node(struct node *node, struct node *inser_node)
{
	struct node *temp_node = NULL;
	temp_node = node->next;

	node->next = inser_node;
	inser_node->pre = node;

	inser_node->next= temp_node;
	temp_node->pre = inser_node;
}
extern CPthreadMutex g_insMutexCalc;

void remov_node(struct node *node)
{
	struct node *pre = NULL;
	struct node *next = NULL;
	pre = node->pre;
	next = node->next;

	pre->next = next;
	next->pre = pre;
	return ;
}

CList *CList::createCList()
{
	CList *pCList = (CList *)base::malloc(sizeof(CList));
	if (pCList)
	{
		pCList->init();
	}
	return pCList;
}

void CList::destroyClist(CList *pCList)
{
	pCList->exit();
	base::free(pCList);
}



void CList::init()
{
	init_node(&head_node);
	tail = &head_node;
	node_num = 0;
}
void CList::exit()
{
}



int CList::push_back(node *pNode)
{
	insert_node(head_node.pre, pNode); 
	tail = pNode;
	++(node_num);
	return 0;

}

node *CList::begin()
{
	return head_node.next;
}

node *CList::back()
{
	return head_node.pre;
}

void CList::pop_front()
{
	node *pNode = head_node.next;
	remov_node(pNode);
	tail = head_node.pre;
	--(node_num);
}

void CList::pop_back()
{
	node *pNode = head_node.pre;
	remov_node(pNode);
	tail = head_node.pre;
	--(node_num);
}

bool CList::empty()
{
	if (node_num == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CList::clear()
{
	node *pNode = NULL;
	#define each_link_node(head, node) for ((node)=(head)->next; (head) != (node); (node)=(node)->next)
	
	each_link_node(&head_node, pNode)
	{
	}		
}

int CList::size()
{
	return node_num;
}

node *CList::getHead()
{
	return &head_node;
}

node *CList::find(node *cmpNode, bool (*cmpFuc)(node *node1, node *node2))
{
	node *pNode = NULL;
	each_link_node(&head_node, pNode)
	{
		if (cmpFuc(cmpNode, pNode))
		{
			return pNode;
		}
	}
	return NULL;
}

node *CList::erase(node *pNode)
{
	node *pNodeNext = pNode->next;
	remov_node(pNode);
	
	tail = head_node.pre;
	--(node_num);
	return pNodeNext;
}

void CStrNode::init(int maxStrLen)
{
	m_strLen = 0;
	m_remainMem = 0;
	if (maxStrLen < 1)
	{
		m_str = NULL;
		return ;
	}
	init_node(&m_node);
	m_str = (char *)base::malloc(maxStrLen + 1);
	m_remainMem = maxStrLen;
	return ;
}

void CStrNode::exit()
{
	base::free(m_str);
	m_str = NULL;
	m_strLen = 0;
}
CStrNode *CStrNode::createCStrNode(int maxStrLen)
{
	CStrNode *pNode = (CStrNode *)base::malloc(sizeof(CStrNode));
	if (pNode)
	{
		pNode->init(maxStrLen);
	}
	return pNode;
}



void CStrNode::destroyCStrNode(CStrNode *pNode)
{
	if (!pNode)
	{
		return ;
	}
	pNode->exit();
	base::free(pNode);
}

int CStrNode::writeStr(char *str)
{
	if (m_remainMem <= 0)
	{
		return 0;
	}
	
	int strLen = (int)strlen(str);
	int writeLen = m_remainMem > strLen ? strLen:m_remainMem;

	memcpy(m_str + m_strLen, str, writeLen);
	m_strLen += writeLen;
	m_remainMem -= writeLen;
	m_str[m_strLen] = '\0';
	return writeLen;
}

node *CStrNode::getNode()
{
	return &m_node;
}
 int CStrNode::size()
{
	return m_strLen;
}

void CStrNode::setStr(char *str, int strLen)
{
	if (strLen == -1)
	{
		strLen = (int)strlen(str);
	}
	m_strLen = strLen;	
	m_str = str;
}

char *CStrNode::getStr()
{
	return m_str;
}


void CString::init()
{
	m_pStrList = CList::createCList();
	m_strLen = 0;
	m_lastStrNode = NULL;
	m_maxStrNodeLen = 32 * 1024;
}

void CString::exit()
{
	CStrNode *pStrNode = NULL; 
	struct node *pNode = NULL;
	while (m_pStrList->size())
	{
		pNode =  m_pStrList->begin();
		pStrNode = TStrNodeContain(pNode);
		m_pStrList->pop_front();
		CStrNode::destroyCStrNode(pStrNode);
	}

	CList::destroyClist(m_pStrList);
	m_pStrList = NULL;
	m_strLen = 0;	
}

void CString::clear()
{
	CStrNode *pStrNode = NULL; 
	struct node *pNode = NULL;
	while (m_pStrList->size())
	{
		pNode =  m_pStrList->begin();
		pStrNode = TStrNodeContain(pNode);
		m_pStrList->pop_front();
		CStrNode::destroyCStrNode(pStrNode);
	}
	m_strLen = 0;
	m_lastStrNode = NULL;
}

CString* CString::createCString()
{
	CString *pCString = (CString *)base::malloc(sizeof(CString));
	if (pCString)
	{
		pCString->init();
	}
	return pCString;
}
 
void CString::destroyCString(CString *pCString)
{
	if (pCString == NULL)
	{
		return ;
	}

	pCString->exit();
	base::free(pCString);
}
 int CString::size()
{
	return m_strLen;
}
 
void CString::append(char *str)
{
	if (str == NULL)
	{
		return ;
	}
	if (!m_lastStrNode)
	{
		m_lastStrNode = CStrNode::createCStrNode(m_maxStrNodeLen);
		m_pStrList->push_back(m_lastStrNode->getNode());
	}
	
	int remainLen = (int)strlen(str);
	int pos = 0;
	int writeLen = 0;

	m_strLen += remainLen;

	while (1)
	{
		writeLen = m_lastStrNode->writeStr(str + pos);
		pos += writeLen;
		remainLen -= writeLen;
		if (remainLen == 0)
		{
			break;
		}
		else
		{
			m_lastStrNode = CStrNode::createCStrNode(m_maxStrNodeLen);
			m_pStrList->push_back(m_lastStrNode->getNode());
		}
	}
}

void CString::append(const char *str)
{
	append((char *)str);
}
char *CString::c_str()
{
	CStrNode *pStrNode = NULL;
	CStrNode *newStrNode = NULL;
	struct node *pNode = NULL;

	if (m_pStrList->size() == 1)
	{
		pNode =  m_pStrList->begin();
		pStrNode = TStrNodeContain(pNode);
		return pStrNode->getStr();
	}
	
	int newStrLen = m_maxStrNodeLen > m_strLen ? m_maxStrNodeLen : m_strLen;
	newStrNode = CStrNode::createCStrNode(newStrLen);
	
	while (m_pStrList->size())
	{
		pNode =  m_pStrList->begin();
		pStrNode = TStrNodeContain(pNode);
		m_pStrList->pop_front();

		newStrNode->writeStr(pStrNode->getStr());
		
		CStrNode::destroyCStrNode(pStrNode);
	}


	m_pStrList->push_back(newStrNode->getNode());
	m_lastStrNode = newStrNode;
	return newStrNode->getStr();
}



CLogDataInf::CLogDataInf() : m_lenSize(4), m_packet(NULL), m_packetLen(0), m_infsNum(0)
{
}

CLogDataInf::~CLogDataInf()
{
	if (m_packet)
	{
		free(m_packet);
		m_packet = NULL;
	}
}

void CLogDataInf::I2CLen(int iLen, char *CLen, int CLenSize)
{
	memset(CLen, 0, CLenSize);
	for (int i=0; i<CLenSize; ++i)
	{
		CLen[i] = iLen;
		iLen = iLen >> 8;
		if (iLen == 0)
		{
			CLen[CLenSize-1] = i + 1;
			break;
		}
	}
	return ;
}

void CLogDataInf::C2ILen(char *CLen, int CLenSize, int &iLen)
{
	iLen = 0;
	for (int i=0; i<CLen[CLenSize-1]; ++i)
	{
		iLen += (unsigned char)(CLen[i]) << (i<<3);
	}
	return ;
}

void CLogDataInf::putInf(char *strdata)
{
	if (m_infsNum >= INF_SIZE)
	{
		return ;
	}
	m_infs[m_infsNum++] = strdata;
	m_packetLen += strlen(strdata) + 1 + m_lenSize;
}

void CLogDataInf::putInf(int intData)
{
	char strData[64];
	base::snprintf(strData, sizeof(strData), "%d", intData);
	putInf(strData);
}

int CLogDataInf::packet()
{
	if (m_packet)
	{
		free(m_packet);
		m_packet = NULL;
	}
	int mallocLen = m_lenSize + m_packetLen + m_lenSize;
	m_packet = (char *)malloc(mallocLen);

	int pos = 0;
	I2CLen(mallocLen, m_packet+pos, m_lenSize);
	pos += m_lenSize;

	char *inf = NULL;
	int infLen = 0;
	for (int i=0; i<m_infsNum; ++i)
	{
		inf = m_infs[i];
		infLen = strlen(inf) + 1;
		I2CLen(infLen, m_packet+pos, m_lenSize);
		pos += m_lenSize;
		memcpy(m_packet+pos, inf, infLen);
		pos += infLen;
	}
	I2CLen(mallocLen, m_packet+pos, m_lenSize);
	return mallocLen;
}
int CLogDataInf::unPacket(char *infs[], int infLens[])
{
	return unPacket(m_packet, infs, infLens);
}
int CLogDataInf::unPacket(char *packet, char *infs[], int infLens[])
{
	int totalLen = 0;
	char *inf = NULL;
	int infLen = 0;
	C2ILen(packet, m_lenSize, totalLen);
	int infsNum = 0;
	int i=m_lenSize;
	for (; i<totalLen-m_lenSize; )
	{
		C2ILen(packet+i,m_lenSize,infLen);
		inf = packet + i + m_lenSize;
		i += infLen;
		infs[infsNum] = inf;
		infLens[infsNum++] = infLen;
		
	}
	C2ILen(packet+i,m_lenSize,infLen);
	if (infLen != totalLen)
	{
		infs[0] = NULL;
		infLens[0] = NULL;
		return 0;
	}
	infs[infsNum] = NULL;
	infLens[infsNum] = NULL;
	return totalLen;
}

void CLogDataInf::calcLens(char *infs[], int infNum, int infLens[])
{
	for (int i=0; i<infNum; ++i)
	{
		infLens[i] = strlen(infs[i]);
	}
}

