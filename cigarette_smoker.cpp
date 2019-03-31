Sempahore TobaccoAndPaper = 0;
Sempahore PaperAndMatches = 0;
Semaphore MatchesAndTobacco = 0;
Sempaphore DoneSmoking = 1;

void agent() 
{
      wait(DoneSmoking);
      int r = rand() % 3;


      switch( r ) {
            case 0: signal(TobaccoAndPaper);
            break;
            case 1: signal(PaperAndMatches);
            break;
            case 2: signal(MatchesAndTobacco);
            break;
      }
}

void Smoker_A()
{
      while(true) {

            
            // Wait for two ingredients
            
            wait(TobaccoAndPaper);
            smoke();

            // Signal that we're done smoking
            // so the next agent can put down ingredients.

            signal(DoneSmoking);
      }
}