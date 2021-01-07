<GameProjectFile>
  <PropertyGroup Type="Node" Name="normal" ID="3bdbd9b7-5e85-43f4-ac07-034838239aa2" Version="2.3.2.3" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000">
        <Timeline ActionTag="30915487" FrameType="VisibleFrame" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Value="True" />
        </Timeline>
        <Timeline ActionTag="30915487" FrameType="ZOrderFrame" Property="ZOrder">
          <IntFrame FrameIndex="0" Value="2" />
        </Timeline>
        <Timeline ActionTag="30915487" FrameType="ColorFrame" Property="CColor">
          <ColorFrame FrameIndex="0" Alpha="111">
            <Color A="255" R="255" G="255" B="255" />
          </ColorFrame>
        </Timeline>
        <Timeline ActionTag="2735732" FrameType="VisibleFrame" Property="VisibleForFrame">
          <BoolFrame FrameIndex="0" Value="True" />
        </Timeline>
        <Timeline ActionTag="2735732" FrameType="ZOrderFrame" Property="ZOrder">
          <IntFrame FrameIndex="0" Value="1" />
        </Timeline>
        <Timeline ActionTag="30915487" Property="Alpha">
          <IntFrame FrameIndex="0" Value="111" />
        </Timeline>
      </Animation>
      <ObjectData Name="red" CanEdit="False" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="shell" ActionTag="30915487" ZOrder="2" Alpha="111" IconVisible="False" ctype="SpriteObjectData">
            <Size X="150.0000" Y="150.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="pic/candy/candy_tm.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="body" ActionTag="2735732" ZOrder="1" IconVisible="False" ctype="SpriteObjectData">
            <Size X="120.0000" Y="120.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="pic/candy/candy_red.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>