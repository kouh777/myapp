package applewatch.apple_watch;

/**
 * Created by KOUHO on 2014/10/13.
 */

import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Canvas;
import android.graphics.drawable.BitmapDrawable;
import android.util.Log;
import android.view.MotionEvent;


public class scene_Menu implements GamePart{

    private Paint m_Paint;
    // image resources
    private BitmapDrawable	m_MenuBack;
    private BitmapDrawable m_ButtonBase;
    private BitmapDrawable m_UiBackGround;

    private BitmapDrawable m_UiPlayerName;
    private BitmapDrawable m_UiPrefacture;
    private BitmapDrawable m_UiWalkingCount;

    private boolean m_bMove;

    private int m_iNextScene;
    private GameView m_GameView;

    private btn_Ranking m_btn_Ranking;
    private btn_Gallery m_btn_Gallery;
    private btn_Gacha   m_btn_Gacha;
    private btn_MyPage  m_btn_MyPage;

    private menu_Character m_Character;
    private btn_Walk m_btn_Walk;

    private MessageCharacter m_MessageCharacter;

    // for test
    private numImage m_numImage;

    // constract
    public scene_Menu(GameView gv){
        m_Paint = null;
        m_iNextScene = 0;
        m_GameView = gv;

        // background resource
        m_MenuBack = (BitmapDrawable)gv.getResources().getDrawable(R.drawable.bg);
        // button background resource
        m_ButtonBase = (BitmapDrawable)gv.getResources().getDrawable(R.drawable.button_base);
        // ui background resource
        m_UiBackGround = (BitmapDrawable)gv.getResources().getDrawable(R.drawable.name_bar);
        // ui player_name resource
        m_UiPlayerName = (BitmapDrawable)gv.getResources().getDrawable(R.drawable.moji_playername);
        // ui prefacture_name resource
        m_UiPrefacture = (BitmapDrawable)gv.getResources().getDrawable(R.drawable.moji_todouhuken);
        // ui walking count resource
        m_UiWalkingCount = (BitmapDrawable)gv.getResources().getDrawable(R.drawable.moji_totalwalk);

        int w = gv.getGameWidth();
        int h = gv.getGameHeight();

        m_btn_MyPage = new btn_MyPage(gv, 0, h-(w>>4)*3);
        m_btn_Gallery = new btn_Gallery(gv, w>>2, h-(w>>4)*3);
        m_btn_Gacha = new btn_Gacha(gv, (w>>2)*2,  h-(w>>4)*3);
        m_btn_Ranking = new btn_Ranking(gv, (w>>2)*3, h-(w>>4)*3);

        m_MessageCharacter = new MessageCharacter(gv, 50, 100);

        // for presentation
        m_btn_Walk = new btn_Walk(gv, (w>>2)*3, h-(w>>1));
        m_Character = new menu_Character(gv, 100, 350);
        m_numImage = new numImage(gv,100,100,1.0f);

        reset();
    }

    @Override
    public void reset(){
        m_bMove = false;
        Log.d("TEST", "Menu::Reset");
    }

    @Override
    // go to next scene
    public boolean move(){
        return m_bMove;
    }

    @Override
    // value of next scene
    public int nextSceneID(){
        return m_iNextScene;
    }

    @Override
    // draw
    public void    draw(Canvas c) {
        int w = m_GameView.getWidth();
        int h = m_GameView.getHeight();
        if (m_MenuBack != null) {
            m_MenuBack.setBounds(0, 0, w, h);
            m_MenuBack.draw(c);
        }
        if(m_UiBackGround != null){
            m_UiBackGround.setBounds(0,0,w,m_UiBackGround.getIntrinsicHeight());
            m_UiBackGround.draw(c);
        }

        // for test ui context
        if(m_UiPlayerName != null){
            m_UiPlayerName.setBounds(
                    370,
                    20,
                    370+m_UiPlayerName.getIntrinsicWidth(),
                    20+m_UiPlayerName.getIntrinsicHeight()
            );
            m_UiPlayerName.draw(c);
        }

        // for test ui context
        if(m_UiPrefacture != null){
            m_UiPrefacture.setBounds(
                    20,
                    20,
                    20+m_UiPrefacture.getIntrinsicWidth(),
                    20+m_UiPrefacture.getIntrinsicHeight()
            );
            m_UiPrefacture.draw(c);
        }

        if(m_UiWalkingCount != null){
            m_UiWalkingCount.setBounds(
                    60,
                    75,
                    60+m_UiWalkingCount.getIntrinsicWidth(),
                    75+m_UiWalkingCount.getIntrinsicHeight()
            );
            m_UiWalkingCount.draw(c);
        }

        /*
        if(m_UiPrefacture != null){
            m_UiPrefacture.setBounds(10,20,m_UiPrefacture.getIntrinsicWidth(),m_UiPrefacture.getIntrinsicHeight());
            m_UiPrefacture.draw(c);
        }
        if(m_UiWalkingCount != null){
            m_UiWalkingCount.setBounds(100,110,m_UiWalkingCount.getIntrinsicWidth(),m_UiWalkingCount.getIntrinsicHeight());
            m_UiWalkingCount.draw(c);
        }
        */


        if (m_ButtonBase != null) {
            m_ButtonBase.setBounds(0, h - (w >> 4) * 3, w, h);
            m_ButtonBase.draw(c);
        }
        if (m_btn_MyPage != null) {
            m_btn_MyPage.draw(c);
        }
        if (m_btn_Ranking != null) {
            m_btn_Ranking.draw(c);
        }
        if (m_btn_Gallery != null) {
            m_btn_Gallery.draw(c);
        }
        if (m_btn_Gacha != null) {
            m_btn_Gacha.draw(c);
        }
        if (m_Character != null) {
            m_Character.draw(c);
        }

        /*
        if (m_numImage != null) {
            m_numImage.draw(c);
        }

        if (m_btn_Walk != null) {
            m_btn_Walk.draw(c);
        }
        */
        if( m_MessageCharacter != null ){
            m_MessageCharacter.draw(c);
        }
    }

    @Override
    // touch event
    public void    touch(MotionEvent event){
        if(m_btn_MyPage != null){
            m_btn_MyPage.touch(event);
            if(m_btn_MyPage.isTouched()){
                m_iNextScene = m_btn_MyPage.nextSceneID();
                m_bMove = true;
            }
        }
        if(m_btn_Ranking != null){
            m_btn_Ranking.touch(event);
            if(m_btn_Ranking.isTouched()){
                m_iNextScene = m_btn_Ranking.nextSceneID();
                m_bMove = true;
            }
        }
        if(m_btn_Gallery != null){
            m_btn_Gallery.touch(event);
            if(m_btn_Gallery.isTouched()){
                m_iNextScene = m_btn_Gallery.nextSceneID();
                m_bMove = true;
            }
        }
        if(m_btn_Gacha != null){
            m_btn_Gacha.touch(event);
            if(m_btn_Gacha.isTouched()){
                m_iNextScene = m_btn_Gacha.nextSceneID();
                m_bMove = true;
            }
        }
        if(m_btn_Walk != null){
            m_btn_Walk.touch(event);
        }
    }
}