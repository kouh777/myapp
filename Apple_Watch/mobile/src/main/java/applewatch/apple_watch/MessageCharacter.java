package applewatch.apple_watch;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.drawable.BitmapDrawable;

/**
 * Created by KOUHO on 2014/11/06.
 */
public class MessageCharacter {
    private BitmapDrawable m_MessageBackGround;
    private String m_MessageStr;
    private GameView m_GameView;
    private int m_iPosX;
    private int m_iPosY;
    private final int m_FontSize = 24;

    public MessageCharacter(GameView gv, int posX, int posY){
        m_GameView = gv;
        m_iPosX = posX;
        m_iPosY = posY;

        // message box resource
        m_MessageBackGround = (BitmapDrawable)gv.getResources().getDrawable(R.drawable.message2);

    }

    public void draw(Canvas c){
        double x = m_iPosX * m_GameView.getGamePerWidth();
        double y = m_iPosY * m_GameView.getGamePerHeight();
        double w = x + m_MessageBackGround.getIntrinsicWidth()  * m_GameView.getGamePerWidth();
        double h = y + m_MessageBackGround.getIntrinsicHeight() * m_GameView.getGamePerHeight();
        double sx = 0.65;
        double sy = 1.0;

        if (m_MessageBackGround != null) {
            m_MessageBackGround.setBounds(
                    (int)x,
                    (int)y,
                    (int)( x + (w * sx) ),
                    (int)( y + (h * sy) )
            );
            m_MessageBackGround.draw(c);
        }
        double paddingX = 20 * m_GameView.getGamePerWidth();
        double paddingY = 50 * m_GameView.getGamePerHeight();

        // text display for test
        Paint paint = new Paint();
        paint.setAntiAlias(true);

        String str = "あなたが走るの？ホント？";
        paint.setTextSize(m_FontSize);
        paint.setColor(Color.BLACK);
        c.drawText( str, (int)(x + paddingX), (int)(y + paddingY), paint );
    }
}
