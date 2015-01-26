package ece493.assignment1;

import android.os.Bundle;
import android.support.v4.app.NavUtils;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.SeekBar;
import android.widget.TextView;

public class SettingsActivity
        extends ActionBarActivity
        implements SeekBar.OnSeekBarChangeListener
{

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

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

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case android.R.id.home:
                NavUtils.navigateUpFromSameTask(this);
                return true;
        }
        return super.onOptionsItemSelected(item);
    }

    private void setSeekBarValue() {
        SeekBar seekBar = (SeekBar)findViewById(R.id.seek_bar);
        TextView seekBarValue = (TextView)findViewById(R.id.seek_bar_value);

        int windowSize = getWindowSize();
        seekBar.setProgress((windowSize - 3) / 2);
        seekBarValue.setText(String.valueOf(windowSize));
    }

    private int getWindowSize() {
        return getSharedPreferences(Settings.NAME, MODE_PRIVATE).getInt(Settings.WINDOW_SIZE, Settings.DEFAULT_WINDOW_SIZE);
    }

    private void setWindowSize(int windowSize) {
        getSharedPreferences(Settings.NAME, MODE_PRIVATE).edit().putInt(Settings.WINDOW_SIZE, windowSize).commit();
    }

    // SeekBar.OnSeekBarChangeListener

    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
        int windowSize = 2 * progress + 3;

        setWindowSize(windowSize);
        TextView seekBarValue = (TextView)findViewById(R.id.seek_bar_value);
        seekBarValue.setText(String.valueOf(windowSize));
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar) { }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar) { }
}
