package ece493.assignment1;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.SeekBar;
import android.widget.TextView;


public class SettingsActivity extends ActionBarActivity implements SeekBar.OnSeekBarChangeListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        SeekBar seekBar = (SeekBar)findViewById(R.id.seek_bar);
        seekBar.setOnSeekBarChangeListener(this);

        setSeekBarValue();
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_settings, menu);
        return true;
    }

    private void setSeekBarValue() {
        SeekBar seekBar = (SeekBar)findViewById(R.id.seek_bar);
        TextView seekBarValue = (TextView)findViewById(R.id.seek_bar_value);

        seekBar.setProgress((Settings.windowSize - 3) / 2);
        seekBarValue.setText(String.valueOf(Settings.windowSize));
    }

    private void setWindowSize(int progress) {
        Settings.windowSize = 2 * progress + 3;
        TextView seekBarValue = (TextView)findViewById(R.id.seek_bar_value);
        seekBarValue.setText(String.valueOf(Settings.windowSize));
    }

    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        setWindowSize(progress);
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) { }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) { }
}
