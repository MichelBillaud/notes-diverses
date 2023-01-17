package mymidiplayer;

import javax.sound.midi.InvalidMidiDataException;
import javax.sound.midi.MidiEvent;
import javax.sound.midi.MidiSystem;
import javax.sound.midi.MidiUnavailableException;
import javax.sound.midi.Sequence;
import javax.sound.midi.Sequencer;
import javax.sound.midi.ShortMessage;
import static javax.sound.midi.ShortMessage.*;
import javax.sound.midi.Track;

/**
 *
 * @author billaud
 */
public class MyMidiPlayer {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws InterruptedException {
        /*
        System.out.println("Enter the number of notes to be played: ");
        Scanner in = new Scanner(System.in);
        int numOfNotes = in.nextInt();*/
        int numOfNotes = 10;

        MyMidiPlayer player = new MyMidiPlayer();
        player.setUpPlayer(numOfNotes);
    }

    public void setUpPlayer(int numOfNotes) throws InterruptedException {

        try {
            final int channel = 2;
            // A static method of MidiSystem that returns 
            // a sequencer instance. 
            Sequencer sequencer = MidiSystem.getSequencer();
            sequencer.open();

            // Creating a sequence. 
            Sequence sequence = new Sequence(Sequence.PPQ, 4);

            // PPQ(Pulse per ticks) is used to specify timing 
            // type and 4 is the timing resolution. 
            // Creating a track on our sequence upon which 
            // MIDI events would be placed 
            Track track = sequence.createTrack();

            int note = 60;
            int instrument = 13;
            track.add(makeEvent(CONTROL_CHANGE, channel, instrument, 0, 1));
            // Adding some events to the track 
            for (int tick = 5; tick < (4 * numOfNotes) + 5; tick += 4) {

                // Add Note On event 
                track.add(makeEvent(NOTE_ON, channel, note, 100, tick));
                //track.add(makeEvent(NOTE_ON, channel, note+3, 100, tick));

                // Add Note Off event 
                track.add(makeEvent(NOTE_OFF, channel, note, 100, tick + 2));
                //track.add(makeEvent(NOTE_OFF, channel, note+3, 100, tick + 2));
                note += 2;
            }

            // Setting our sequence so that the sequencer can 
            // run it on synthesizer 
            sequencer.setSequence(sequence);

            // Specifies the beat rate in beats per minute. 
            sequencer.setTempoInBPM(120);

            // Sequencer starts to play notes 
            sequencer.start();

            while (sequencer.isRunning()) {
                // Exit the program when sequencer has stopped playing. 
                Thread.sleep(1000);
                System.out.println("Waiting");
            
            }
                    sequencer.close();
                    System.exit(1);
            
        } catch (InvalidMidiDataException | MidiUnavailableException ex) {
            System.err.println(ex);
        }
    }

    public MidiEvent makeEvent(int command, int channel,
            int note, int velocity, int tick) {

        MidiEvent event = null;

        try {

            // ShortMessage stores a note as command type, channel, 
            // instrument it has to be played on and its speed. 
            ShortMessage a = new ShortMessage();
            a.setMessage(command, channel, note, velocity);

            // A midi event is comprised of a short message(representing 
            // a note) and the tick at which that note has to be played 
            event = new MidiEvent(a, tick);
        } catch (InvalidMidiDataException ex) {
        }
        return event;
    }
}
