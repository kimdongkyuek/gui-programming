using G26W07WFCardDealer.Model;

namespace G26W07WFCardDealer {
    public partial class Form1 : Form {
        private readonly Deck deck = new Deck();
        private PictureBox[] cardBoxes = [];

        public Form1() {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e) {
            cardBoxes = [card1, card2, card3, card4, card5];
        }

        private void OnDeal(object sender, EventArgs e) {
            deck.Reset();                                   // 52장으로 되돌리고
            deck.Shuffle();                                 // 섞은 다음
            List<Card> hand = deck.Deal(cardBoxes.Length);  // 5장을 떼어낸다 (중복 불가)

            for (int i = 0; i < cardBoxes.Length; i++) {
                cardBoxes[i].Image = LoadCardImage(hand[i]);
            }

            // 판별은 모델이 하고, View는 결과를 받아 보여주기만 한다
            labelRank.Text = PokerEvaluator.Evaluate(hand).ToKorean();
        }

        // 모델의 Card를 리소스 이름으로 바꾸는 일은 View 담당.
        // 그림이 2벌인 것도 이미지 쪽 사정이라 모델이 알 필요가 없다.
        private static Image LoadCardImage(Card card) {
            string value = card.Rank switch {
                Rank.Ace => "ace",
                Rank.Jack => "jack",
                Rank.Queen => "queen",
                Rank.King => "king",
                _ => ((int)card.Rank).ToString()
            };

            string suit = card.Suit.ToString().ToLower();

            if (card.IsFace) {
                suit += "2";
            }

            return Properties.Resources.ResourceManager.GetObject($"{value}_of_{suit}") as Image
                ?? Properties.Resources.red_joker;
        }
    }
}
