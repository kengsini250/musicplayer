#include "dir.h"

void openDir(QMainWindow* p,QDir* path)
{
    QString d = QFileDialog::getExistingDirectory(
        p, "Open Music Dir",
        ".",
        QFileDialog::ShowDirsOnly
        | QFileDialog::DontResolveSymlinks);
    if (d.isEmpty())
        path->setPath(".");
    else
        path->setPath(d);
}

void addFolder(QDir* path, QString _path, MusicList* list)
{
    QString a = path->path() + "/" + _path;
    path->setPath(a);

    QFileInfo tmpCurrTarget(path->path());

    if (!tmpCurrTarget.isDir())    //is music
    {
        list->addMusic(path->path(), _path);
        //saveload.save(list);//auto save

    }
    else {    //is dir
        QStringList allFile = path->entryList();
        allFile.removeOne(".");
        allFile.removeOne("..");
        for (int i = 0; i < allFile.count(); i++) {
            QString p = path->path() + "/" + allFile[i];
            QFileInfo currTarget(p);
            if (currTarget.isDir())
            {
                addFolder(path,allFile[i],list);
            }
            else
            {
                list->addMusic(path->path() + "/" + allFile[i], allFile[i]);
                //saveload.save(list);//auto save
            }
        }
    }
    QString b = path->path() + "/..";
    path->setPath(b);
    path->setPath(path->absolutePath());

}
