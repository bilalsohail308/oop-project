// FormWindow.h
#ifndef FORMWINDOW_H
#define FORMWINDOW_H

#include <string>
#include <vector>
// Function to open a modal form window
;
bool openEFormWindow(std::string& name, std::string& description, int& price, std::vector<std::string>& imagePaths);
bool openFormWindow(std::string& name, std::string& description, int& price, std::vector<std::string>& imagePaths);


#endif // FORMWINDOW_H
