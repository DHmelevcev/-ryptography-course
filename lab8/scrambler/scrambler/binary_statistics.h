#pragma once
#include <vector>
#include <map>

// получение статистики критери€ хи-квадрат ѕирсона
double chi_squared_statistic(const std::vector<bool>& sample);

// получение сбалансированности
double balance_statistic(const std::vector<bool>& sample);

// поучение циклов
std::map<size_t, size_t> cyclicality_statistic(const std::vector<bool>& sample);

// получение коррел€ции
double correlation_statistic(const std::vector<bool>& sample);