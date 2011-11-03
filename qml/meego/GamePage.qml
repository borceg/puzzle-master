import QtQuick 1.1
import com.nokia.meego 1.0
import com.meego.extras 1.0
import net.venemo.puzzlemaster 2.0

Page
{
    id: gamePage

    PuzzleBoard
    {
        id: puzzleBoard
    }

    Component.onCompleted: puzzleBoard.startGame("qrc:/aaa.jpg", 3, 3, true);
}
