#pragma once
#include "framework.h"
#include "pch.h"

#include "ArchivistException.h"

namespace HYDRA15::Foundation::Archivist
{
    // �ṹ�����ݵĽڵ㣬���Դ��棺
    //   - �κ��������ͣ���Ϊ�յ�ʹ��
    //   - �ض��������ͣ���Ϊ�ڵ�ʹ��
    //      - ӳ�䣨std::unordered_map<Entry, Entry>��
    //      - �б�std::deque<Entry>��
    //      - ���У�std::queue<Entry>��
    class Entry
    {
    public:
        enum class Type
        {
            empty = 0,
            endpoint,
            map,
            list,
            queue
        };

        // ��������
    private:
        Type type = Type::empty;
        std::any data;
        std::any assistData;

        // ��������
    private:
        using Pair = std::pair<Entry, Entry>;
        using ListAssist = size_t;
        using QueueAssist = std::pair<size_t, size_t>; // pair<frontIndex, backIndex>
    public: 
        using Map = std::unordered_map<Entry, Entry>;

        // ����
    public:
        // ��������
        Entry() = default;
        Entry(const Entry& other) = default;
        virtual ~Entry() = default;

        // ͨ����ʼ���б��죬������Ϊ��Ӧ������
        Entry(std::initializer_list<Pair> list);
        explicit Entry(std::initializer_list<Entry> list);

        // ͨ���������ݹ��죬����������Σ�������ɶ�Ӧ����������
        template<typename T>
        Entry(const T& t);

        // ֱ�ӳ�ʼ��Ϊ��Ӧ������
        Entry(Type t);

        // ������������
        Entry& operator[](const Entry& key);          // Key���ͣ�֧���������͵ļ�

        // �����޸�����Ϣ
    public:
        // ��С���
        size_t size() const;
        void resize(size_t size);

        // ����Ԫ��
        void push(const Entry& entry);
        void pop();
        Entry& front();
        Entry& back();

        // �������
        bool empty() const;
        void clear();

        // �������
        Type get_entry_type() const;
        const std::type_info& get_data_type() const;

        // ������֧��
        Map::iterator begin();
        Map::iterator end();
    };




}