package ece493.assignment1;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.annotation.NonNull;
import android.support.v7.app.ActionBarActivity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.FileNotFoundException;
import java.io.InputStream;


/**
 * The main activity, responsible for displaying the image.
 * Includes commands for executing the Mean and Median filters,
 * and navigation to Settings and Image Selection.
 */
public class ImageViewer extends ActionBarActivity {

    final int SELECT_IMAGE_REQUEST = 1;

    Menu _menu;

    // These can both be null - it means no image is selected.

    // We store this so that we can reload the image that was last used when the app is restarted,
    // i.e. on a configuration change.
    Uri _uri;
    // We store this so that we can pass it to the filters.  We can't necessarily get the
    // original bitmap from the ImageView object.
    Bitmap _bitmap;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_image_viewer);
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        _menu = menu;
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_image_viewer, menu);

        // This goes here, because onRestoreInstanceState is called before this function,
        // but we need the menu to exist before we set the image, because the visibility of
        // certain menu options depends on whether or not an image is set.
        setImageFromCurrentUri();
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        switch (id) {
            case R.id.action_settings:
                openSettings();
                return true;
            case R.id.action_select_image:
                selectImage();
                return true;
            case R.id.action_mean_filter:
                new MeanFilterTask().execute(_bitmap);
                return true;
            case R.id.action_median_filter:
                new MedianFilterTask().execute(_bitmap);
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        if (_uri != null) {
            outState.putString("URI", _uri.toString());
        }
    }

    @Override
    protected void onRestoreInstanceState(@NonNull Bundle inState) {
        String uriString = inState.getString("URI");
        if (uriString != null) {
            _uri = Uri.parse(uriString);
        }
    }

    protected void onActivityResult(int requestCode, int resultCode, Intent intent) {
        switch(requestCode) {
            case SELECT_IMAGE_REQUEST:
                if (resultCode == RESULT_OK) {
                    _uri = intent.getData();
                    setImageFromCurrentUri();
                }
                break;
        }
    }

    private void setImageFromCurrentUri() {
        if (_uri == null) {
            return;
        }

        try {
            InputStream imageStream = getContentResolver().openInputStream(_uri);
            Bitmap image = BitmapFactory.decodeStream(imageStream);

            setImage(image);
        }
        catch (FileNotFoundException ex) {
            _uri = null;
        }
    }

    private void openSettings() {
        Intent toOpenSettings = new Intent(this, SettingsActivity.class);
        startActivity(toOpenSettings);
    }

    private void selectImage() {
        Intent toSelectPhoto = new Intent(Intent.ACTION_PICK);
        toSelectPhoto.setType("image/*");
        startActivityForResult(toSelectPhoto, SELECT_IMAGE_REQUEST);
    }

    private void setImage(Bitmap image) {
        ImageView imageView = (ImageView)findViewById(R.id.image_view);
        TextView textView = (TextView)findViewById(R.id.text_view);
        MenuItem meanFilterMenuItem = _menu.findItem(R.id.action_mean_filter);
        MenuItem medianFilterMenuItem = _menu.findItem(R.id.action_median_filter);

        if (image == null) {
            imageView.setVisibility(View.GONE);
            textView.setVisibility(View.VISIBLE);
            meanFilterMenuItem.setVisible(false);
            medianFilterMenuItem.setVisible(false);
        }
        else {
            imageView.setVisibility(View.VISIBLE);
            textView.setVisibility(View.GONE);
            meanFilterMenuItem.setVisible(true);
            medianFilterMenuItem.setVisible(true);

            imageView.setImageBitmap(image);
        }

        _bitmap = image;
    }

    public void text_view_Click(View view) {
        selectImage();
    }

    private int getWindowSize() {
        return getSharedPreferences(Settings.NAME, MODE_PRIVATE).getInt(Settings.WINDOW_SIZE, Settings.DEFAULT_WINDOW_SIZE);
    }

    private abstract class ConvolutionFilterTask extends AsyncTask<Bitmap, Integer, Bitmap> {
        @Override
        protected void onPreExecute() {
            TextView progressText = (TextView)findViewById(R.id.progress_text);
            progressText.setVisibility(View.VISIBLE);
            progressText.setText("0%");

            MenuItem meanFilterItem = _menu.findItem(R.id.action_mean_filter);
            meanFilterItem.setVisible(false);

            MenuItem medianFilterItem = _menu.findItem(R.id.action_median_filter);
            medianFilterItem.setVisible(false);

            MenuItem selectImageItem = _menu.findItem(R.id.action_select_image);
            selectImageItem.setVisible(false);
        }

        @Override
        protected void onProgressUpdate(Integer... progress) {
            TextView progressText = (TextView)findViewById(R.id.progress_text);
            progressText.setText(String.format("%d%%", progress[0]));
        }

        @Override
        protected void onPostExecute(Bitmap result) {
            TextView progressText = (TextView)findViewById(R.id.progress_text);
            progressText.setVisibility(View.GONE);

            MenuItem meanFilterItem = _menu.findItem(R.id.action_mean_filter);
            meanFilterItem.setVisible(true);

            MenuItem medianFilterItem = _menu.findItem(R.id.action_median_filter);
            medianFilterItem.setVisible(true);

            MenuItem selectImageItem = _menu.findItem(R.id.action_select_image);
            selectImageItem.setVisible(true);

            setImage(result);
            Toast.makeText(ImageViewer.this, "Finished!", Toast.LENGTH_LONG).show();
        }

        protected native Bitmap applyMeanFilterImpl(Bitmap bitmap, int windowSize);
        protected native Bitmap applyMedianFilterImpl(Bitmap bitmap, int windowSize);
    }

    private class MeanFilterTask extends ConvolutionFilterTask {
        @Override
        protected Bitmap doInBackground(Bitmap... params) {
            return applyMeanFilterImpl(params[0], getWindowSize());
        }
    }

    private class MedianFilterTask extends ConvolutionFilterTask {
        @Override
        protected Bitmap doInBackground(Bitmap... params) {
            return applyMedianFilterImpl(params[0], getWindowSize());
        }
    }

    static {
        System.loadLibrary("convolution-filter");
    }
}
