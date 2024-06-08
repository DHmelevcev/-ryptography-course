#pragma once
#include <vector>
#include <map>

// ��������� ���������� �������� ��-������� �������
double chi_squared_statistic(const std::vector<bool>& sample);

// ��������� ������������������
double balance_statistic(const std::vector<bool>& sample);

// �������� ������
std::map<size_t, size_t> cyclicality_statistic(const std::vector<bool>& sample);

// ��������� ����������
double correlation_statistic(const std::vector<bool>& sample);