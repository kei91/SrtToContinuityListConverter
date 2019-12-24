#ifndef DOCCONTROLLER_H
#define DOCCONTROLLER_H

class MainWindow;

// Will handle convertation to .doc formate
class DocController
{
public:
    void SetMainWindow(MainWindow* MainWindow);

private:
    MainWindow* m_MainWindow;
};

#endif // DOCCONTROLLER_H
