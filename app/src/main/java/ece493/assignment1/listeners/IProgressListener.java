package ece493.assignment1.listeners;

/**
 * Created by Isaac on 2015-01-18.
 */
public interface IProgressListener {
    public void progressStarted(int maxProgress);
    public void incrementProgress();
    public void progressFinished();
}
