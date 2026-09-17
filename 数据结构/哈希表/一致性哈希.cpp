#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>
#include <list>
#include <string>
#include "md5.h"

using namespace std;

using uint = unsigned int;

class PhysicalHost;

class VirtualHost
{
public:
    VirtualHost(string ip, PhysicalHost *physicalhost) : IP(ip), physicalhost(physicalhost)
    {
        md5 = ::getMD5(ip.c_str());
    }
    string get_IP() const
    {
        return IP;
    }
    uint get_md5() const
    {
        return md5;
    }
    PhysicalHost *get_physicalhost() const
    {
        return physicalhost;
    }
    bool operator<(const VirtualHost &other) const
    {
        if (md5 != other.md5)
        {
            return md5 < other.md5;
        }
        return IP < other.IP;
    }
    bool operator==(const VirtualHost &other) const
    {
        return IP == other.IP;
    }

private:
    string IP;
    uint md5;
    PhysicalHost *physicalhost;
};

class PhysicalHost
{
public:
    PhysicalHost(string ip, int number) : IP(ip)
    {
        for (int i = 0; i < number; i++)
        {
            virtual_list.emplace_back(ip + "#" + to_string(i), this);
        }
    }
    const list<VirtualHost> &get_virtual_list() const
    {
        return virtual_list;
    }
    string get_IP()
    {
        return IP;
    }

private:
    string IP;
    list<VirtualHost> virtual_list;
};

class ConsistentHash
{
public:
    void add_host(const PhysicalHost &p_host)
    {
        for (const auto &host : p_host.get_virtual_list())
        {
            virtual_circle.insert(host);
        }
    }
    void delete_host(const PhysicalHost &p_host)
    {
        for (const auto &host : p_host.get_virtual_list())
        {
            auto it = virtual_circle.find(host);
            if (it != virtual_circle.end())
            {
                virtual_circle.erase(it);
            }
        }
    }
    string find_host(string client_ip)
    {
        uint md5 = ::getMD5(client_ip.c_str());
        for (auto host : virtual_circle)
        {
            if (host.get_md5() >= md5)
            {
                return host.get_physicalhost()->get_IP();
            }
        }
        if (virtual_circle.empty())
        {
            throw runtime_error("哈希环中没有物理服务器");
        }
        return virtual_circle.begin()->get_physicalhost()->get_IP();
    }

private:
    set<VirtualHost> virtual_circle;
};

void show(vector<string> client_ips,ConsistentHash &chash)
{
    map<string, list<string>> map1;
    for (auto val : client_ips)
    {
        string host_ip = chash.find_host(val);
        map1[host_ip].emplace_back(val);
    }
    for (auto val : map1)
    {
        cout << val.first << endl;
        for (auto val1 : val.second)
        {
            cout << val1 << endl;
        }
        cout<<endl;
    }
}

void test_1()
{
    PhysicalHost host1("10.0.0.1", 150);
    PhysicalHost host2("10.0.0.2", 150);
    PhysicalHost host3("10.0.0.3", 150);

    vector<string> client_ips = {
        "192.168.1.101",
        "192.168.1.102",
        "192.168.1.103",
        "192.168.1.104",
        "192.168.1.105",
        "192.168.1.106",
        "192.168.1.107",
        "192.168.1.108",
        "192.168.1.109",
        "192.168.1.110",
        "192.168.1.111",
        "192.168.1.112",
        "192.168.1.113",
        "192.168.1.114",
        "192.168.1.115"};

    ConsistentHash chash;
    chash.add_host(host1);
    chash.add_host(host2);
    chash.add_host(host3);

    // cout<<chash.find_host("192.168.1.101")<<endl;
    show(client_ips,chash);
    chash.delete_host(host2);
    show(client_ips,chash);
}

int main()
{
    test_1();
    return 0;
}