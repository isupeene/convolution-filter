package ece493.assignment1;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.audiofx.BassBoost;
import android.net.Uri;
import android.os.AsyncTask;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import java.io.FileNotFoundException;
import java.io.InputStream;


public class ImageViewer extends ActionBarActivity {

    final int SELECT_IMAGE_REQUEST = 1;
    final String TAG = "ImageViewer";

    Menu _menu;
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
                applyMeanFilter();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    protected void onActivityResult(int requestCode, int resultCode, Intent intent) {
        switch(requestCode) {
            case SELECT_IMAGE_REQUEST:
                if (resultCode == RESULT_OK) {
                    try {
                        Uri imageUri = intent.getData();
                        InputStream imageStream = getContentResolver().openInputStream(imageUri);
                        Bitmap image = BitmapFactory.decodeStream(imageStream);

                        setImage(image);
                    }
                    catch (FileNotFoundException ex) {
                        Log.wtf(TAG, ex);
                    }
                }
                break;
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
        if (image == null) {
            imageView.setVisibility(View.GONE);
            textView.setVisibility(View.VISIBLE);
            meanFilterMenuItem.setVisible(false);
        }
        else {
            imageView.setVisibility(View.VISIBLE);
            textView.setVisibility(View.GONE);
            meanFilterMenuItem.setVisible(true);

            imageView.setImageBitmap(image);
        }

        _bitmap = image;
    }

    private void applyMeanFilter() {
        if (_bitmap == null) {
            Log.wtf(TAG, "applyMeanFilter called when no image was present!");
            Toast.makeText(this, "No image available to filter!", Toast.LENGTH_LONG).show();
        }
        else {
            new ConvolutionFilterTask().execute(_bitmap);
        }
    }

    public void text_view_Click(View view) {
        selectImage();
    }

    private int getWindowSize() {
        return getSharedPreferences(Settings.NAME, MODE_PRIVATE).getInt(Settings.WINDOW_SIZE, Settings.DEFAULT_WINDOW_SIZE);
    }

    private class ConvolutionFilterTask extends AsyncTask<Bitmap, Integer, Bitmap> {
        @Override
        protected void onPreExecute() {
//                ProgressBar progressBar = (ProgressBar) findViewById(R.id.progress_bar);
//
//                progressBar.setVisibility(View.VISIBLE);
//                progressBar.setMax(maxProgress);
//                progressBar.setProgress(0);
            TextView progressText = (TextView)findViewById(R.id.progress_text);
            progressText.setVisibility(View.VISIBLE);
            progressText.setText("0%");

            MenuItem meanFilterItem = _menu.findItem(R.id.action_mean_filter);
            meanFilterItem.setVisible(false);

            MenuItem selectImageItem = _menu.findItem(R.id.action_select_image);
            selectImageItem.setVisible(false);
        }

        @Override
        protected Bitmap doInBackground(Bitmap... params) {
            return applyMeanFilterImpl(params[0], getWindowSize());
        }

        @Override
        protected void onProgressUpdate(Integer... progress) {
//                ProgressBar progressBar = (ProgressBar) findViewById(R.id.progress_bar);
//
//                progressBar.incrementProgressBy(1);
            TextView progressText = (TextView)findViewById(R.id.progress_text);
            progressText.setText(String.format("%d%%", progress[0]));
        }

        @Override
        protected void onPostExecute(Bitmap result) {
//                ProgressBar progressBar = (ProgressBar) findViewById(R.id.progress_bar);
//
//                progressBar.setVisibility(View.GONE);
            TextView progressText = (TextView)findViewById(R.id.progress_text);
            progressText.setVisibility(View.GONE);

            MenuItem meanFilterItem = _menu.findItem(R.id.action_mean_filter);
            meanFilterItem.setVisible(true);

            MenuItem selectImageItem = _menu.findItem(R.id.action_select_image);
            selectImageItem.setVisible(true);

            setImage(result);
            Toast.makeText(ImageViewer.this, "We set the image!", Toast.LENGTH_LONG).show();
        }

        public native Bitmap applyMeanFilterImpl(Bitmap bitmap, int windowSize);
    }

    static {
        System.loadLibrary("convolution-filter");
    }
}
