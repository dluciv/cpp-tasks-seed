#ifndef GAUSS_SOLVE_H
#define GAUSS_SOLVE_H

#include <Eigen/Dense>
#include <string>

Eigen::MatrixXd read_csv(const std::string& filename);
void write_csv(const std::string& filename, const Eigen::VectorXd& x);
Eigen::VectorXd solve_gauss(Eigen::MatrixXd AB);

#endif