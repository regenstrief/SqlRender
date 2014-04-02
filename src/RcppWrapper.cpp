
#include <Rcpp.h>
#include "SqlRender.h"

//using namespace Rcpp;

// [[Rcpp::export]]
Rcpp::List renderSqlInternal(std::string sql, Rcpp::List parameters) {

  using namespace ohdsi::sqlRender;

	try {
		//Convert list to map:
		SqlRender::ParameterMap parameterToValue;
		Rcpp::List names = parameters.attr("names");
		for (unsigned int i = 0; i < parameters.size(); i++) {
			parameterToValue[names[i]] = Rcpp::as<std::string>(parameters[i]);
		}

		SqlRender::String renderedSql = SqlRender::renderSql(sql, parameterToValue);
		return Rcpp::List::create(Rcpp::Named("parameterizedSql") = sql, Rcpp::Named("sql") = renderedSql, Rcpp::Named("parameters") = parameterToValue);

	} catch (std::exception &e) {
		forward_exception_to_r(e);
	} catch (...) {
		::Rf_error("c++ exception (unknown reason)");
	}
  return Rcpp::List::create();
}