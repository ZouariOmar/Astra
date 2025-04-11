/**
 * @file      PdfGenerator.hpp
 * @author    @ZouariOmar (zouariomar20@gmail.com)
 * @brief     PdfGenerator header file
 * @version   0.1
 * @date      2025-04-10
 * @copyright Copyright (c) 2025
 * @link https://github.com/ZouariOmar/Astra/project/inc/PdfGenerator.hpp PdfGenerator.hpp @endlink
 */

//? Pre-Processor prototype declaration part
#ifndef __PDF_GENERATOR_HPP__
#define __PDF_GENERATOR_HPP__

//? Include prototype declaration part
//* Include std Qt header(s)
#include <QtWidgets/QMainWindow>

//* Include custom header(s)
#include "../inc/Employees.hpp"


//? Class(es) prototype declaration part

class PdfGenerator {
public:
  static const unsigned int generatePdf(const QString &filePath, const SqlParam &);
}; // PdfGenerator class

#endif // __PDF_GENERATOR_HPP__
